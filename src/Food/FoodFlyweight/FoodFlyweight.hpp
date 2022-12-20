#ifndef SnakeGame__FOOD_FLYWEIGHT_HPP
#define SnakeGame__FOOD_FLYWEIGHT_HPP
#include "../../TextureManager/TextureManager.hpp"
#include <memory>
enum class FoodName { APPLE = 0, WATER_MELON, STAR_FRUIT, BURGER, HOTDOG, STEAK };

enum class FoodType { InEdible, Edible };

typedef struct FoodModel {
  TextureManager Texture;
  int PointsForFood;
  FoodType Type;
} FoodModel;

class FoodFlyweight {
private:
  using ValueType = FoodModel;
  using PointerType = ValueType *;
  using ReferenceType = ValueType &;

  using FoodMapType = std::unordered_map<FoodName, std::shared_ptr<ValueType>>;

public:
  FoodFlyweight();
  ~FoodFlyweight();

  void AddFood(FoodName name, FoodType type, int points_for_food, const std::string &texture_path);
  void RemoveFood(FoodName name);
  
 [[nodiscard]] std::shared_ptr<ValueType> get_FoodModel(FoodName name);
private:
  FoodMapType m_FoodMap;
};
#endif // SnakeGame__FOOD_FLYWEIGHT_HPP