cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(FoodFlyweight_Sources FoodFlyweight.cpp)
set(FoodFlyweight_Headers FoodFlyweight.hpp)

add_executable(FoodFlyweight ${FoodFlyweight_Sources} ${FoodFlyweight_Headers})
target_include_directories(FoodFlyweight PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(FoodFlyweight Food)

set_target_properties(FoodFlyweight PROPERTIES LINKER_LANGUAGE CXX)  