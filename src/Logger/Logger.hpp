#ifndef UTILS_LOGGER_HPP
#define UTILS_LOGGER_HPP
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

#define LOG_CURRENT_LINE std::to_string(__LINE__)
#define LOG_FUNCTION_NAME std::string(__FUNCTION__) + std::string("()")

struct LoggerInfo {
  std::string operator()(const std::string &str) const {
    return "\x1B[35m" + str + "\033[0m";
  }
};

struct LoggerSuccess {
  std::string operator()(const std::string &str) const {
    return "\x1B[32m" + str + "\033[0m";
  }
};

struct LoggerWarn {
  std::string operator()(const std::string &str) const {
    return "\x1B[93m" + str + "\033[0m";
  }
};

struct LoggerError {
  std::string operator()(const std::string &str) const {
    return "\x1B[31m" + str + "\033[0m";
  }
};

struct LoggerNullLevel {
  std::string operator()(const std::string &str) const { return str; }
};

enum class NotifyType { INFO, SUCCESS, WARN, ERROR, EMPTY };

#define NOTIFY_INFO NotifyLevel(NotifyType::INFO)
#define NOTIFY_SUCCESS NotifyLevel(NotifyType::SUCCESS)
#define NOTIFY_WARN NotifyLevel(NotifyType::WARN)
#define NOTIFY_ERROR NotifyLevel(NotifyType::ERROR)
#define NOTIFY_EMPTY NotifyLevel(NotifyType::EMPTY)

union NotifyLevel {
  NotifyLevel() {}
  NotifyLevel(NotifyType type) : type_(type) {}
  std::string operator()(const std::string &str) const {
    switch (type_) {
    case NotifyType::INFO: {
      return log_info(str);
      break;
    }
    case NotifyType::SUCCESS: {
      return log_success(str);
      break;
    }
    case NotifyType::WARN: {
      return log_warn(str);
      break;
    }
    case NotifyType::ERROR: {
      return log_err(str);
      break;
    };

    case NotifyType::EMPTY: {
      return log_empty(str);
      break;
    }
    } // !switch
    return "";
  }
  NotifyType type_;
  LoggerInfo log_info;
  LoggerSuccess log_success;
  LoggerWarn log_warn;
  LoggerError log_err;

  LoggerNullLevel log_empty;
};

namespace ContentFormat {
typedef std::vector<std::string> content_format_type_t;
typedef content_format_type_t (*content_cb_format_t)();

/**
 * @brief used to set content format which looks like this Subsystem : a , Status: b, Line: c, Message: d
*/
inline content_format_type_t SubsystemFormat() {
  content_format_type_t format;
  format.push_back("Subsystem: ");
  format.push_back("Status: ");
  format.push_back("Line: ");
  format.push_back("Message: ");
  return format;
}

inline content_format_type_t ExpressionFormat() {
  content_format_type_t format;
  format.push_back("Expression: ");
  format.push_back("Status: ");
  format.push_back("Line: ");
  format.push_back("Message: ");
  return format;
}

}; // namespace ContentFormat

struct MessageModel {
  MessageModel(const std::string &msg, NotifyType level = NotifyType::EMPTY)
      : msg_(msg), level_(level) {}
  std::string msg_;
  NotifyType level_;
  std::pair<std::string, NotifyType> get_pair() {
    return std::make_pair(msg_, level_);
  }
};

#define MESSAGE_ERROR(msg) MessageModel(msg,NotifyType::ERROR)
#define MESSAGE_INFO(msg) MessageModel(msg,NotifyType::INFO)
#define MESSAGE_SUCCESS(msg) MessageModel(msg,NotifyType::SUCCESS)
#define MESSAGE_WARN(msg) MessageModel(msg,NotifyType::WARN)

namespace logContent {
struct Content;

using content_pair_type_t           = std::pair<std::string, NotifyLevel>;
using content_pair_ref_type_t       = content_pair_type_t &;
using content_pair_const_ref_type_t = const content_pair_ref_type_t;

struct ContentModel {
  std::string sContentName;
};

struct Content {
private:
  using size_type               = unsigned int;
  using ContentCallbackFormat_t = ContentFormat::content_cb_format_t;
  using ContentFormat_t         = ContentFormat::content_format_type_t;

public:
  ContentModel contentModel;
  std::vector<content_pair_type_t> content;
  ContentCallbackFormat_t contentFormat;
  Content() = default;
  Content(const std::string &content_name) : contentFormat(nullptr) {
    contentModel.sContentName = std::move(content_name);
  }
  ~Content() = default;

  void push_back(content_pair_type_t l_content) {
    (content.push_back(l_content));
  }

  void SetFormat(ContentCallbackFormat_t format_cb) {
    this->contentFormat = format_cb;
  }

  inline std::string GetFormattedContent() {
    if (contentFormat == nullptr) {
      throw std::logic_error("content format not provided");
    }

    auto get_notify_str =
        [](content_pair_const_ref_type_t content) -> std::string {
      return content.second(content.first);
    };

    std::string res("    ");
    res.reserve(50);

    ContentFormat_t format = (contentFormat)();
    if(format.empty()){
      throw std::logic_error("probably you provided not working format callback");
    }

    if (content.empty()) {
      return res;
    }
    format[0] += contentModel.sContentName + ", ";

    size_type content_size = content.size();
    for (int i = 0, format_index = 1; i < content.size() && format_index < format.size(); i++,format_index++) {
      format[format_index] += get_notify_str(content[i]) + std::string((content_size > 1) ? ", " : " ");
      content_size--;
    }

    for (int i = 0; i < format.size(); i++) {
      res += format[i];
    }
    return res;
  }

  inline void clear() { content.clear(); }

  inline bool empty() const { return content.empty(); }
};

}; // namespace logContent

namespace logMethod {
using content_type_t           = logContent::Content;
using content_ref_type_t       = content_type_t &;
using content_const_ref_type_t = const content_ref_type_t;

using size_type                = unsigned int;
using ContentCallbackFormat_t  = ContentFormat::content_cb_format_t;
using ContentFormat_t          = ContentFormat::content_format_type_t;

struct formatMethod {
  std::string operator()(const std::string &str) const {
    std::string ret = "  \x1B[36m+Method: " + str + "\033[0m\n";
    return ret;
  };
};

struct MethodModel {
  MethodModel() : ExecutionTime(-1), sMethodName("", 1) {}
  std::vector<content_type_t> content;
  std::unordered_map<std::string, int> contentId;
  std::string sMethodName;
  double ExecutionTime;
  std::string sTimeUnit;
};

template <class _Tp, class... _Types>
using all_same = std::enable_if_t<std::conjunction_v<std::is_same<_Tp, _Types>...>>;

template <typename T>
using IsReference = std::enable_if_t<std::is_reference_v<T>>;

template <typename T>
using IsNotReference = std::enable_if_t<not std::is_reference_v<T>>;

class Method {
private:
  MethodModel m_model;

public:
  Method(const std::string &method_name) {
    this->m_model.sMethodName = method_name;
    m_model.sTimeUnit = "";
  };
  ~Method() = default;

  template <typename... Args, class = all_same<MessageModel, Args...>>
  inline void AddContent(const std::string &content_name, Args... args) {
      (GetContent(content_name).push_back(args.get_pair()), ...);
  }
  template <typename _Type,class = IsNotReference<_Type> >
  inline void AddContent(const std::string &content_name,_Type&& model) {
    GetContent(content_name).push_back(model.get_pair());
  }

  inline content_ref_type_t GetContent(size_type index) {
    if (index >= m_model.content.size()) {
      throw std::out_of_range("Out of range");
    }
    return m_model.content[index];
  }

  inline content_ref_type_t GetContent(const std::string &content_name) {
    if (m_model.contentId.count(content_name) == 0) {
      content_type_t local_content(content_name);
      m_model.contentId[content_name] = m_model.content.size();
      m_model.content.push_back(local_content);
    }
    return m_model.content[m_model.contentId[content_name]];
  }

  void SetExecutionTime(double execution_time, const std::string& time_unit) {
    m_model.ExecutionTime = execution_time;
    this->m_model.sTimeUnit = time_unit;
  }
  
  double GetExecutionTime() const { return m_model.ExecutionTime; }

  inline size_type GetContentSize() const { return m_model.content.size(); }

  std::string GetMethodName() const {
    formatMethod format;
    return format(m_model.sMethodName);
  }
  /**
   * @brief clears method
  */
  inline void clear() {
    m_model.content.clear();
    m_model.contentId.clear();
  }
  
  std::string GetMethodSummary(){
    if(GetExecutionTime() < 0) return "";
    LoggerInfo log_info;
    std::string res = log_info("[summary] ");

    res += log_info("Execution time: " + std::to_string(GetExecutionTime()) + " " + m_model.sTimeUnit);
    return res;
  }
  inline bool empty() const { return m_model.content.empty(); }
};

}; // namespace logMethod

namespace logModule {
using log_method_t = logMethod::Method;
using log_method_ref_t = log_method_t&;
using log_const_method_ref_t = const log_method_ref_t;

struct ModuleModel {
  ModuleModel() {}
  ~ModuleModel() = default;
  std::string sModuleName;
  std::string sFileName;
};

struct formatModule {
  std::string operator()(const std::string &str) const {
    std::string ret = std::string("\x1B[93m* Module: ") + str + "\033[0m\n";
    return ret;
  }
};

class Module {
private:
  using size_type = unsigned int;

private:
  std::vector<log_method_t> m_methods;
  std::unordered_map<std::string, size_type> m_MethodId;
  ModuleModel m_model;
  bool m_bShown = false;

public:
  Module(const std::string &module_name, const std::string &file_name = "")
      : m_bShown(false) {
    m_model.sModuleName = module_name;
    m_model.sFileName = file_name;
  }
  ~Module() = default;

  void AddMethod(const std::string &method_name) {
    if (m_MethodId.count(method_name) == 0) {
      m_MethodId[method_name] = m_methods.size();
      m_methods.push_back(log_method_t(method_name));
    }
  }

  log_method_ref_t GetMethod(size_type index) {
    if (index >= m_methods.size()) {
      throw std::out_of_range("Out of range");
    }

    return m_methods[index];
  }

  log_method_ref_t GetMethod(const std::string &method_name) {
    AddMethod(method_name);

    return m_methods[m_MethodId[method_name]];
  }

  inline std::string GetModuleName() {
    formatModule format;
    return format(m_model.sModuleName);
  }
  /**
  @brief clears module
  */
  inline void clear() {
    m_methods.clear();
    m_MethodId.clear();
  }

  inline bool empty() const { return m_MethodId.empty(); }

  inline bool isShown() const { return m_bShown; }

  inline void SetShown(bool state) { m_bShown = state; }

  inline size_type GetMethodsSize() const { return m_methods.size(); }
};

}; // namespace logModule

#define LOG_INSTANCE Logger::GetLogger()

class Logger;

class LoggerDestroyer {
private:
  Logger *p_instance;

public:
  ~LoggerDestroyer();
  void initialize(Logger *p);
};

class Logger {
private:
  using method_t           = logMethod::Method;
  using method_ref_t       = method_t &;
  using const_method_ref_t = const method_ref_t;

  using module_t           = logModule::Module;
  using module_ref_t       = module_t &;
  using const_module_ref_t = const module_ref_t;

  using size_type          = unsigned int;

private:
  static Logger *p_instance;
  static LoggerDestroyer destroyer;

protected:
  Logger() {}
  Logger(const Logger &);
  Logger &operator=(Logger &);
  ~Logger() {
      for(int i = 0;i<m_modules.size();i++){
        PrintModule(GetModule(i));
      }
   }
  friend class LoggerDestroyer;

public:
  static Logger &GetLogger();

  inline void AddModule(const std::string &module_name) {
    if (m_ModuleId.count(module_name) == 0) {
      m_ModuleId[module_name] = m_modules.size();
      m_modules.push_back(module_t(module_name));
    }
  }

  inline module_ref_t GetModule(size_type index) {
    if (index >= m_modules.size())
      throw std::out_of_range("Out of range");
    return m_modules[index];
  }

  inline module_ref_t GetModule(const std::string &module_name) {
    return m_modules[m_ModuleId[module_name]];
  }

  size_type Size() const { return m_modules.size(); }

  module_ref_t operator[](const std::string &module_name) {
    if (m_ModuleId.count(module_name) == 0) {
      m_ModuleId[module_name] = m_modules.size();
      m_modules.push_back(module_t(module_name));
    }
    return m_modules[m_ModuleId[module_name]];
  }

  inline void PrintModule(const_module_ref_t Module) {
    if (Module.empty())
      return;
      
    bool containsContent = false;
    for(int i = 0;i<Module.GetMethodsSize();i++){
      auto& method_context = Module.GetMethod(i);
      if(!method_context.empty()){
        containsContent = true;
      }
      
      if (!Module.isShown() && containsContent){
        std::cout << Module.GetModuleName();
        break;
      }
    }

    for (int i = 0; i < Module.GetMethodsSize(); i++) {
      auto &function_context = Module.GetMethod(i);

      if (function_context.empty())
        continue;

      std::cout << function_context.GetMethodName();

      for (int k = 0; k < function_context.GetContentSize(); k++) {
        std::cout << function_context.GetContent(k).GetFormattedContent() << '\n';
      }

      if (function_context.GetExecutionTime() > -1) {
        std::cout << function_context.GetMethodSummary()  << '\n';
      }
      function_context.clear();
    }
    Module.clear();
    Module.SetShown(true);
  }

private:
  std::vector<module_t> m_modules;
  std::unordered_map<std::string, size_type> m_ModuleId;
};

#endif //! UTILS_LOGGER_HPP
