cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Timer_Sources Timer.cpp)
set(Timer_Headers Timer.hpp)

add_executable(Timer ${Timer_Sources} ${Timer_Headers})
target_include_directories(Timer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Timer PROPERTIES LINKER_LANGUAGE CXX)