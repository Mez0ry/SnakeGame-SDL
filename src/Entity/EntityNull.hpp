#ifndef SnakeGame_ENTITY_NULL_OBJECT_HPP
#define SnakeGame_ENTITY_NULL_OBJECT_HPP
#include "Entity.hpp"
class EntityNull : public Entity {
public:
  EntityNull() {};
  ~EntityNull() {};

  void Update() {}
  void Render() {}

  const EntityPosition &get_PositionOnMap() const { return EntityPosition(); }
  bool isPlayer() const { return false; }

private:
};
#endif // !SnakeGame_ENTITY_NULL_OBJECT_HPP