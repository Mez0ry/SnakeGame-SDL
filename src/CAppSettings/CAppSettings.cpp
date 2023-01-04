#include "CAppSettings.hpp"

CAppSettings::CAppSettings() { m_SlashSymbol = GetSlashSymbol; }

CAppSettings::~CAppSettings() {}

CAppSettings &CAppSettings::instance() {
  static CAppSettings instance;

  return instance;
}

void CAppSettings::LoadSettings() {
  Timer FunctionTimer("CAppSettings::LoadSettings()");
  m_ConfigPath = m_SrcFolderPath + m_SlashSymbol + "CAppSettings" + m_SlashSymbol + "AppConfig" + m_SlashSymbol + "config.cfg";

  if (Serializer::Deserialize(m_Serializer, m_ConfigPath)) {
    std::cout << "App settings successfuly deserialized" << '\n';
  }
}

int CAppSettings::get_WindowHeight() const {
  return m_Serializer["SnakeGame-SDL Settings"]["window_height"].get_Int(0);
}

int CAppSettings::get_WindowWidth() const {
  return m_Serializer["SnakeGame-SDL Settings"]["window_width"].get_Int(0);
}

int CAppSettings::get_MapHeight() const {
  return m_Serializer["SnakeGame-SDL Settings"]["map_height"].get_Int(0);
}

int CAppSettings::get_MapWidth() const {
  return m_Serializer["SnakeGame-SDL Settings"]["map_width"].get_Int(0);
}

bool CAppSettings::get_FullScreen() const {
  return m_Serializer["SnakeGame-SDL Settings"]["fullscreen_mode"].get_Bool(0);
}

void CAppSettings::set_SourceFolder(char *source_folder) {
  std::function<std::string(std::string &)> correct_path =
      [&](const std::string &str) -> std::string {
    std::string res;

    std::string cpy_str(str);
    cpy_str.erase(cpy_str.find_last_not_of(m_SlashSymbol) + 1);

    auto get_last_word = [&](const std::string &str) -> std::string {
      std::string str_out(str);
      str_out.erase(0, str_out.find_last_of(m_SlashSymbol) + 1);
      return str_out;
    };

    std::string last_word = get_last_word(cpy_str);
    if (last_word == "build") {

      size_t last_occurence_index = cpy_str.find_last_of(m_SlashSymbol);
      res = cpy_str.substr(0, last_occurence_index);
      res += m_SlashSymbol + std::string("src");
    } else if (last_word == "executable") {
      size_t last_occurence_index = cpy_str.find_last_of(m_SlashSymbol);
      res = cpy_str.substr(0, last_occurence_index);
    }
    return res;
  };

  std::string tmp_str = source_folder;
  this->m_SrcFolderPath = correct_path(tmp_str);
 
}