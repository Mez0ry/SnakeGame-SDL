cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(FontManager_Sources FontManager.cpp)
set(FontManager_Headers FontManager.hpp)

add_executable(FontManager ${FontManager_Sources} ${FontManager_Headers})
target_include_directories(FontManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(FontManager PROPERTIES LINKER_LANGUAGE CXX)