#include "Game.hpp"
#include "CAppSettings/CAppSettings.hpp"

int main(int agrc, char **argv) {
  char source_folder_path[FILENAME_MAX];

  if (!GetCurrentDir(source_folder_path, sizeof(source_folder_path))) {
    return errno;
  }

  CAppSettings::instance().set_SourceFolder(source_folder_path);
  CAppSettings::instance().LoadSettings();
  
  Game gm;
  gm.Run();

  return 0;
}