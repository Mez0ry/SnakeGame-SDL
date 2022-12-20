cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Achievements_Sources FiveHundredScore.cpp OneHundredScore.cpp OneThousandScore.cpp)
set(Achievements_Headers FiveHundredScore.hpp OneHundredScore.hpp OneThousandScore.hpp)

add_executable(Achievements ${Achievements_Sources} ${Achievements_Headers})
target_include_directories(Achievements PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Achievements AchievementSystem)

set_target_properties(Achievements PROPERTIES LINKER_LANGUAGE CXX)