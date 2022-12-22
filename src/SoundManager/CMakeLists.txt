cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(SoundManager_Sources SoundManager.cpp)
set(SoundManager_Headers SoundManager.hpp)

add_executable(SoundManager ${SoundManager_Sources} ${SoundManager_Headers})
target_include_directories(SoundManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(SoundManager PROPERTIES LINKER_LANGUAGE CXX)