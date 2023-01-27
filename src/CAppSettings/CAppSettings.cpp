#ifndef __CAPPSETTINGS_H__
#define __CAPPSETTINGS_H__

#include "CAppSettings.hpp"

CAppSettings::CAppSettings() { m_SlashSymbol = GetSlashSymbol; }

CAppSettings::~CAppSettings() {}

CAppSettings &CAppSettings::instance()
{
  static CAppSettings instance;

  return instance;
}

void CAppSettings::LoadSettings()
{
  Utils::Timestamp timestamp;
  m_ConfigPath = m_SrcFolderPath + m_SlashSymbol + "CAppSettings" + m_SlashSymbol + "AppConfig" + m_SlashSymbol + "config.cfg";

  auto &module_context = LOG_INSTANCE["CAppSettings"];
  auto &function_context = module_context.GetMethod(LOG_FUNCTION_NAME);

  const auto &settings_format = []() -> ContentFormat::content_format_type_t
  {
    ContentFormat::content_format_type_t format;
    format.push_back("  property: ");
    format.push_back("  value: ");
    return format;
  };

  if (Serializer::Deserialize(m_Serializer, m_ConfigPath))
  {
    function_context.AddContent("Serializer::Deserialize",MESSAGE_SUCCESS("Success"), MessageModel(LOG_CURRENT_LINE),MESSAGE_SUCCESS("App settings successfully deserialized"));
    function_context.GetContent("Serializer::Deserialize").SetFormat(ContentFormat::SubsystemFormat);
    
    function_context.AddContent("window_height", MESSAGE_SUCCESS(std::to_string(get_WindowHeight())));
    function_context.GetContent("window_height").SetFormat(settings_format);

    function_context.AddContent("window_width", MESSAGE_SUCCESS(std::to_string(get_WindowWidth())));
    function_context.GetContent("window_width").SetFormat(settings_format);

    function_context.AddContent("map_height", MESSAGE_SUCCESS(std::to_string(get_MapHeight())));
    function_context.GetContent("map_height").SetFormat(settings_format);

    function_context.AddContent("map_width", MESSAGE_SUCCESS(std::to_string(get_MapWidth())));
    function_context.GetContent("map_width").SetFormat(settings_format);

    function_context.AddContent("fullscreen_mode", MESSAGE_SUCCESS(m_Serializer["SnakeGame-SDL Settings"]["fullscreen_mode"].get_String(0)));
    function_context.GetContent("fullscreen_mode").SetFormat(settings_format);
  }

  function_context.SetExecutionTime(timestamp.GetDurationInMs(), "ms");
  LOG_INSTANCE.PrintModule(module_context);
}

int CAppSettings::get_WindowHeight() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["window_height"].get_Int(0);
}

int CAppSettings::get_WindowWidth() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["window_width"].get_Int(0);
}

int CAppSettings::get_MapHeight() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["map_height"].get_Int(0);
}

int CAppSettings::get_MapWidth() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["map_width"].get_Int(0);
}

bool CAppSettings::get_FullScreen() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["fullscreen_mode"].get_Bool(0);
}

void CAppSettings::set_SourceFolder(char *source_folder)
{
  std::function<std::string(std::string &)> correct_path =
      [&](const std::string &str) -> std::string
  {
    std::string res;

    std::string cpy_str(str);
    cpy_str.erase(cpy_str.find_last_not_of(m_SlashSymbol) + 1);

    auto get_last_word = [&](const std::string &str) -> std::string
    {
      std::string str_out(str);
      str_out.erase(0, str_out.find_last_of(m_SlashSymbol) + 1);
      return str_out;
    };

    std::string last_word = get_last_word(cpy_str);
    if (last_word == "build")
    {

      size_t last_occurence_index = cpy_str.find_last_of(m_SlashSymbol);
      res = cpy_str.substr(0, last_occurence_index);
      res += m_SlashSymbol + std::string("src");
    }
    else if (last_word == "executable")
    {
      size_t last_occurence_index = cpy_str.find_last_of(m_SlashSymbol);
      res = cpy_str.substr(0, last_occurence_index);
    }
    return res;
  };

  std::string tmp_str = source_folder;
  this->m_SrcFolderPath = "/home/mezory/Documents/Repositories/SnakeGameSDLnew/src";//correct_path(tmp_str);
}
#endif // __CAPPSETTINGS_H__