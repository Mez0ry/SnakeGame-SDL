#ifndef SnakeGame_ACHIEVEMENT_SETTINGS_HPP
#define SnakeGame_ACHIEVEMENT_SETTINGS_HPP
#include <vector>
#include <variant>
#include "string.h"

#include "../Achievement.hpp"
#include "../Achievements/OneHundredScore.hpp"
#include "../Achievements/FiveHundredScore.hpp"
#include "../Achievements/OneThousandScore.hpp"

namespace AchievementInternal {
using var_t = std::variant<OneHundredScore, FiveHundredScore, OneThousandScore>;
};

class AchievementSettings{
public:
AchievementSettings();
~AchievementSettings();

void ParseConfigFile(std::vector<AchievementInternal::var_t>& vec_out);
/**
 * @brief Updates achievements status (Unlocked / Not unlocked)
*/
void UpdateConfigAttribs(std::vector<AchievementInternal::var_t>& vec_in);

private:
std::string m_ConfigPath;
};
#endif //!SnakeGame_ACHIEVEMENT_SETTINGS_HPP