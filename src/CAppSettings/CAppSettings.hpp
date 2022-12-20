#ifndef SnakeGame_CAppSettings_HPP
#define SnakeGame_CAppSettings_HPP

#include <stdio.h> /* defines FILENAME_MAX */
#if defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
#include <direct.h>
#define GetCurrentDir _getcwd
#define GetSlashSymbol = "\\";
#define __FILENAME__ \
  (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    defined(__gnu_linux)
#include <unistd.h>
#define GetCurrentDir getcwd
#define GetSlashSymbol '/';
#define __FILENAME__ \
  (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#include <string.h>

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "../Timer/Timer.hpp"

class CAppSettings {
 private:
  using SettingsMapType = std::unordered_map<unsigned int, std::string>;
  SettingsMapType m_SettingsMap;

  std::string m_ConfigPath;
  std::string m_SlashSymbol;
  std::string m_SrcFolderPath;

 public:
  CAppSettings();
  ~CAppSettings();

  static CAppSettings& instance();
  /**
   * @brief Reads config file and adding settings to the map
  */
  void LoadSettings();

  const std::string& get_SlashSymbol() const { return this->m_SlashSymbol; }
  const std::string& get_SourceFolder() const { return m_SrcFolderPath; }

  void set_SourceFolder(char* source_folder);

  int get_WindowHeight() const;
  int get_WindowWidth() const;
  int get_MapHeight() const;
  int get_MapWidth() const;
  bool get_FullScreen() const;

 private:
};
#endif  //! SnakeGame_CAppSettings_HPP