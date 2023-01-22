set(FOOD_FLYWEIGHT FoodFlyweight/FoodFlyweight.hpp FoodFlyweight/FoodFlyweight.cpp)

add_library(Food SHARED ${FOOD_FLYWEIGHT} Food.hpp Food.cpp)