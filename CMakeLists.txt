cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

set(ProjectName SnakeGameSDL)
project(${ProjectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)