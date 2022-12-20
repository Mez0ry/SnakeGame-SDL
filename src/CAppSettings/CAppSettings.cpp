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
  Timer FunctionTimer("CAppSettings::LoadSettings()");
  m_ConfigPath = m_SrcFolderPath + m_SlashSymbol + "CAppSettings" + m_SlashSymbol + "AppConfig" + m_SlashSymbol + "config.cfg";

  std::ifstream file_to_read(m_ConfigPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);

  if (!file_to_read.is_open())
  {
    std::cerr << "Failed to open config file."
              << " "
              << "Config path: " << m_ConfigPath.c_str() << "\nFilename: " << __FILENAME__;
    std::exit(1);
  }

  std::string current_line;
  current_line.reserve(40);
  unsigned int line_counter = 0;
  std::string value;
  value.reserve(20);
  while (getline(file_to_read, current_line))
  {
    // Getting the last word from a string
    for (size_t read_index = 0; read_index < current_line.size(); read_index++)
    {
      if (current_line[read_index] == ' ')
      {
        value.clear();
      }
      else
      {
        value += current_line[read_index];
      }
    }

    if (!value.empty())
    {
      value.resize(value.size() - 1);
    }

    m_SettingsMap.emplace(line_counter, value);
    line_counter++;
    value.clear();
  }
  file_to_read.close();
}

int CAppSettings::get_WindowHeight() const
{
  SettingsMapType::const_iterator it = m_SettingsMap.find(0);
  if (it != m_SettingsMap.end())
  {
    return std::stoi(it->second);
  }

  return -1;
}

int CAppSettings::get_WindowWidth() const
{
  SettingsMapType::const_iterator it = m_SettingsMap.find(1);
  if (it != m_SettingsMap.end())
  {
    return std::stoi(it->second);
  }
  return -1;
}

int CAppSettings::get_MapHeight() const
{
  SettingsMapType::const_iterator it = m_SettingsMap.find(2);
  if (it != m_SettingsMap.end())
  {
    return std::stoi(it->second);
  }

  return -1;
}

int CAppSettings::get_MapWidth() const
{
  SettingsMapType::const_iterator it = m_SettingsMap.find(3);
  if (it != m_SettingsMap.end())
  {
    return std::stoi(it->second);
  }
  return -1;
}

bool CAppSettings::get_FullScreen() const
{
  SettingsMapType::const_iterator it = m_SettingsMap.find(4);
  if (it != m_SettingsMap.end())
  {
    bool res = std::stoi(it->second);
    return res;
  }
  return -1;
}

void CAppSettings::set_SourceFolder(char *source_folder)
{
  #define RELEASE 0
  #if RELEASE
  this->m_SrcFolderPath = std::move(source_folder);
  m_SrcFolderPath.resize(m_SrcFolderPath.find_last_of(m_SlashSymbol));
  #else
  this->m_SrcFolderPath = "/home/mezory/Documents/Repositories/SnakeGameSDLnew/src";
  #endif
}