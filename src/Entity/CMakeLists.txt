cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Entity_Headers Entity.hpp EntityNull.hpp)

add_executable(Entity ${Entity_Headers})
target_include_directories(Entity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Entity PROPERTIES LINKER_LANGUAGE CXX)