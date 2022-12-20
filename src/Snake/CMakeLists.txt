cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Snake_Sources Snake.cpp SnakeBody.cpp)
set(Snake_Headers ISnakeStates.hpp Snake.hpp SnakeBody.hpp)

add_executable(Snake ${Snake_Sources} ${Snake_Headers})
target_include_directories(Snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Snake PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET Snake PROPERTY ENABLE_EXPORTS 1)

add_subdirectory(SnakeStates)