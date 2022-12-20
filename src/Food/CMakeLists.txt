cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(Food_Sources Food.cpp)
set(Food_Headers Food.hpp)

add_executable(Food ${Food_Sources} ${Food_Headers})
target_include_directories(Food PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Food PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET Food PROPERTY ENABLE_EXPORTS 1)

add_subdirectory(FoodFlyweight)