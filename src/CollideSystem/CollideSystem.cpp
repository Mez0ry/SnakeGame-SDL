#include "CollideSystem.hpp"

CollideSystem::CollideSystem() {}

CollideSystem::~CollideSystem() {}

bool CollideSystem::IsColliding(Entity &ent_lhs, Entity &ent_rhs) {
  if (ent_lhs.GetPosition() == ent_rhs.GetPosition()) {
    if (ent_lhs.isPlayer()) {
      Notify(ent_rhs, ENTITY_IS_COLLIDING_WITH_FOOD);
    }
    return true;
  }
  return false;
}
