cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(SnakeStates_Sources IdleState.cpp MovingState.cpp SnakeStatesController.cpp)
set(SnakeStates_Headers IdleState.hpp MovingState.hpp SnakeStatesController.hpp)

add_executable(SnakeStates ${SnakeStates_Sources} ${SnakeStates_Headers})
target_include_directories(SnakeStates PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(SnakeStates PROPERTIES LINKER_LANGUAGE CXX)
