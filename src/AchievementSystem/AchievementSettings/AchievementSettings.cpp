#include "AchievementSettings.hpp"

AchievementSettings::AchievementSettings()
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    m_ConfigPath = CAppSettings::instance().get_SourceFolder() + symbol + "AchievementSystem" + symbol + "AchievementSettings" + symbol + "AchievementConfig" + symbol + "config.cfg";
}

AchievementSettings::~AchievementSettings()
{
}

void AchievementSettings::ParseConfigFile(std::vector<AchievementInternal::var_t> &vec_out)
{
    Timer FunctionTimer;

    std::fstream write_config_file(m_ConfigPath.c_str(), std::ios::out | std::ios::in | std::ios::app | std::ios::binary);

    std::ifstream read_config_file(m_ConfigPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);

    if (!write_config_file.is_open() || !read_config_file.is_open())
    {
        std::cerr << "Failed to open  Achievement config file." << " "<< "Achievement config path: " << m_ConfigPath.c_str() << "\nFilename: " << __FILENAME__;
    }

    std::string str_from_file;
    bool file_is_rewrited = false;
    while (getline(read_config_file, str_from_file))
    {
        if (vec_out.size() > str_from_file.length())
        {
            int size_diff = vec_out.size() - str_from_file.length();
            for (int i = 0; i < size_diff; i++)
            {
                write_config_file << static_cast<int>(std::visit([](auto &&arg) -> bool{ 
                    return arg.IsUnlocked(); 
                }, *((vec_out.end()) - (i + 1))));
            }
            file_is_rewrited = true;
        }

    }
    write_config_file.close();

    if(file_is_rewrited){
        read_config_file.close();
        read_config_file.open(m_ConfigPath.c_str(), std::ios::out | std::ios::app | std::ios::binary);

        if(!read_config_file.is_open()){
          std::cerr << "Failed to open  Achievement config file." << " "<< "Achievement config path: " << m_ConfigPath.c_str() << "\nFilename: " << __FILENAME__;
        }

         while (getline(read_config_file, str_from_file)){
            
         }
    }

    int line_counter = 0;
    for (auto && it = vec_out.begin(); it != vec_out.end(); ++it)
    {
            std::visit([&](auto&& arg){
                
                int ascii_numbers_stars_at = 48; /*In ASCII numbers start from 48*/
                bool value = (int)str_from_file[line_counter] - ascii_numbers_stars_at;
                arg.set_IsUnlocked(value);
            }, (*it));
            line_counter++;
    }

    read_config_file.close();
}

void AchievementSettings::UpdateConfigAttribs(std::vector<AchievementInternal::var_t> &vec_in)
{
   std::fstream write_config_file(m_ConfigPath.c_str(), std::ios::out  | std::ios::in | std::ios::binary | std::ios::trunc);
    if(!write_config_file.is_open()){
          std::cerr << "Failed to open  Achievement config file." << " "<< "Achievement config path: " << m_ConfigPath.c_str() << "\nFilename: " << __FILENAME__;
    }

   for(auto&& it = vec_in.begin(); it != vec_in.end();++it){
    int ascii_numbers_stars_at = 48; /*In ASCII numbers start from 48*/
     std::visit([&](auto && arg){
         write_config_file << static_cast<char>((arg.IsUnlocked() + ascii_numbers_stars_at));
     },(*it));
   }
   write_config_file.close();
}