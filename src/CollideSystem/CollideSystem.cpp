#include "CollideSystem.hpp"

CollideSystem::CollideSystem() {}

CollideSystem::~CollideSystem() {}

bool CollideSystem::IsColliding(Entity &ent_lhs, Entity &ent_rhs) {
  if (ent_lhs.get_PositionOnMap().x == ent_rhs.get_PositionOnMap().x && ent_lhs.get_PositionOnMap().y == ent_rhs.get_PositionOnMap().y) {
    if (ent_lhs.isPlayer()) {
      Notify(ent_rhs, ENTITY_IS_COLLIDING_WITH_FOOD);
    }
    return true;
  }
  return false;
}
