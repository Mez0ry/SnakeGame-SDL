#ifndef SnakeGame_FOOD_HPP
#define SnakeGame_FOOD_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Map.hpp"
#include <random>
#include "FoodFlyweight/FoodFlyweight.hpp"
/** Entity base class*/
#include "../Entity/Entity.hpp"
#define FOOD_SIZE 8

class Food : public Entity {
public:
  Food();
  ~Food();
  void Update();
  void Render();

  void set_MapState(SquareType **map_state);
  void set_FoodFlyweight(const std::shared_ptr<FoodFlyweight>& pFoodFlyweight);

  void LoadTexture(const char *path);

  void set_DstRect(int x, int y, int w, int h);
  void set_SrcRect(int x, int y, int w, int h);

  inline void set_PositionOnMap(int x, int y) { m_Position.x = x; /*\n*/ m_Position.y = y; }

  const EntityPosition &get_PositionOnMap() const override { return m_Position; }

  inline int get_PointsForFood() const { return m_pFoodModel->PointsForFood; }
  inline const FoodType& get_FoodType() const {return m_pFoodModel->Type;}
  void RespawnNewFood();
 
  bool isColliding(const EntityPosition& pos);

  bool isPlayer() const override { return false; }
private:
  enum food_internal_constants{
    RESPAWN_INEDIBLE_FOOD_IN = 25 // used to respawn inedible food every X seconds
  };
  void randomizePositionOnMap();
  void randomizeFoodTexture();
  std::shared_ptr<FoodModel> m_pFoodModel;

  EntityPosition m_Position;
  SquareType **m_MapState;
  std::shared_ptr<FoodFlyweight> m_pFoodFlyweight;
  Utils::Timestamp m_TimeStamp;
};
#endif //! SnakeGame_FOOD_HPP