
set(ACHIEVEMENT Achievement/Achievement.hpp Achievement/AchievementAnimation.hpp)

set(ACHIEVEMENT_SYSTEM AchievementSystem.hpp AchievementSystem.cpp)

add_library(AchievementSystem SHARED ${ACHIEVEMENT_SYSTEM} ${ACHIEVEMENT})