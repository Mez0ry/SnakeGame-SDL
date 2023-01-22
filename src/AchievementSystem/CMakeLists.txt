set(ACHIEVEMENTS Achievements/OneHundredScore.hpp Achievements/OneHundredScore.cpp 
                 Achievements/FiveHundredScore.hpp Achievements/FiveHundredScore.cpp 
                 Achievements/OneThousandScore.hpp Achievements/OneThousandScore.cpp)

set(ACHIEVEMENT_SETTINGS AchievementSettings/AchievementSettings.hpp AchievementSettings/AchievementSettings.cpp)

set(ACHIEVEMENT_SYSTEM Achievement.hpp AchievementSystem.hpp AchievementSystem.cpp)

add_library(AchievementSystem SHARED ${ACHIEVEMENTS} ${ACHIEVEMENT_SETTINGS} ${ACHIEVEMENT_SYSTEM})