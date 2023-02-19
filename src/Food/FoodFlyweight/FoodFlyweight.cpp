#include "FoodFlyweight.hpp"
FoodFlyweight::FoodFlyweight() {}

FoodFlyweight::~FoodFlyweight() {}

void FoodFlyweight::AddFood(FoodName name, FoodType type, int points_for_food, const std::string &texture_path) {

  FoodMapType::iterator it = m_FoodMap.find(name);
  if (it == m_FoodMap.end()) {
    FoodModel model;
    model.PointsForFood = points_for_food;
    model.Type = type;
    model.texture.set_Rect(0,0,32,32);
    model.texture.set_Rect<SourceRect>(0,0,32,32);
    
    m_FoodMap.insert(std::make_pair(name, std::make_shared<FoodModel>(model)));

    m_FoodMap.at(name)->texture.LoadTexture(texture_path);
  }

}

void FoodFlyweight::RemoveFood(FoodName name) {
  FoodMapType::iterator it = m_FoodMap.find(name);
  if (it != m_FoodMap.end()) {
    m_FoodMap.erase(it);
  }
}

std::shared_ptr<FoodFlyweight::ValueType> FoodFlyweight::get_FoodModel(FoodName name) {
  FoodMapType::iterator it = m_FoodMap.find(name);

  if (it != m_FoodMap.end()) {
    return it->second;
  }

  return nullptr;
}
