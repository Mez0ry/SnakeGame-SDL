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

#include "../Timestamp/Timestamp.hpp"
#include "../Serializer/Serializer.hpp"
#include "../Logger/Logger.hpp"

class CAppSettings
{
private:
  Serializer m_Serializer;

  std::string m_ConfigPath;
  std::string m_SlashSymbol;
  std::string m_SrcFolderPath;

public:
  CAppSettings();
  ~CAppSettings();

  static CAppSettings &instance();
  /**
   * @brief Deserializing config file
   */
  void LoadSettings();

  const std::string &get_SourceFolder() const { return m_SrcFolderPath; }

  void set_SourceFolder(char *source_folder);

  int get_WindowHeight() const;
  int get_WindowWidth() const;
  int get_MapHeight() const;
  int get_MapWidth() const;
  bool get_FullScreen() const;

  [[nodiscard]] static std::string GetCorrectedPath(const std::string& path){
    std::string res;
    res.reserve(100);
    for(int i = 0;i<path.size();i++){
      if(path[i] == '/' || path[i] == '\\'){
        res.append(instance().get_SlashSymbol());
      }else{
        res.append(1,path.at(i));
      }
       
    }
    return res;
  }

private:
  const std::string &get_SlashSymbol() const { return this->m_SlashSymbol; }
};
#endif //! SnakeGame_CAppSettings_HPP