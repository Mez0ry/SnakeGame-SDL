cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(CollideSystem_Sources CollideSystem.cpp)
set(CollideSystem_Headers CollideSystem.hpp)

add_executable(CollideSystem ${CollideSystem_Sources} ${CollideSystem_Headers})
target_include_directories(CollideSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(CollideSystem PROPERTIES LINKER_LANGUAGE CXX)