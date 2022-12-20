cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CAppSettings_Sources CAppSettings.cpp)
set(CAppSettings_Headers CAppSettings.hpp)

add_executable(CAppSettings ${CAppSettings_Sources} ${CAppSettings_Headers})
target_include_directories(CAppSettings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CAppSettings PROPERTIES LINKER_LANGUAGE CXX)