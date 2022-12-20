cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(AchievementSystem_Sources AchievementSystem.cpp)
set(AchievementSystem_Headers AchievementSystem.hpp Achievement.hpp)

add_executable(AchievementSystem ${AchievementSystem_Sources} ${AchievementSystem_Headers})
target_include_directories(AchievementSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(AchievementSystem PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET AchievementSystem PROPERTY ENABLE_EXPORTS 1)


add_subdirectory(Achievements)
add_subdirectory(AchievementSettings)