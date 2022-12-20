cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(SpriteAnimation_Sources SpriteAnimation.cpp)
set(SpriteAnimation_Headers SpriteAnimation.hpp)

add_executable(SpriteAnimation ${SpriteAnimation_Sources} ${SpriteAnimation_Headers})
target_include_directories(SpriteAnimation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(SpriteAnimation PROPERTIES LINKER_LANGUAGE CXX)