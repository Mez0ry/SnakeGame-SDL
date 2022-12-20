cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(TextureManager_Sources TextureManager.cpp)
set(TextureManager_Headers TextureManager.hpp)

add_executable(TextureManager ${TextureManager_Sources} ${TextureManager_Headers})
target_include_directories(TextureManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(TextureManager PROPERTIES LINKER_LANGUAGE CXX)