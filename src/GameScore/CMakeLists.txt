cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(GameScore_Sources GameScore.cpp)
set(GameScore_Headers GameScore.hpp)

add_executable(GameScore ${GameScore_Sources} ${GameScore_Headers})
target_include_directories(GameScore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(GameScore PROPERTIES LINKER_LANGUAGE CXX)