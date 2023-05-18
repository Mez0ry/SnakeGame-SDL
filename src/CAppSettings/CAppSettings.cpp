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

    function_context.AddContent("fullscreen_mode", MESSAGE_SUCCESS(m_Serializer["SnakeGame-SDL Settings"]["fullscreen_mode"].GetAs<std::string>(0)));
    function_context.GetContent("fullscreen_mode").SetFormat(settings_format);
  }

  function_context.SetExecutionTime(timestamp.GetDurationInMs(), "ms");
  LOG_INSTANCE.PrintModule(module_context);
}

int CAppSettings::get_WindowHeight() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["window_height"].GetAs<int>(0);
}

int CAppSettings::get_WindowWidth() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["window_width"].GetAs<int>(0);
}

int CAppSettings::get_MapHeight() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["map_height"].GetAs<int>(0);
}

int CAppSettings::get_MapWidth() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["map_width"].GetAs<int>(0);
}

bool CAppSettings::get_FullScreen() const
{
  return m_Serializer["SnakeGame-SDL Settings"]["fullscreen_mode"].GetAs<bool>(0);
}

void CAppSettings::set_SourceFolder(char *source_folder)
{
  namespace fs = std::filesystem;
  fs::path path = fs::current_path();
  
  std::string res;
  if(path.filename() == "build"){
    res = path.parent_path();
    res += std::string(m_SlashSymbol + std::string("src"));
  }else{
    res = path.parent_path();
  }

  this->m_SrcFolderPath = res;
}
#endif // __CAPPSETTINGS_H__