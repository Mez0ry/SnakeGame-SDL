#ifndef SnakeGame_OBSERVER_EVENTS_HPP
#define SnakeGame_OBSERVER_EVENTS_HPP
#include <stdint.h>
enum ObserverEvents : uint32_t {
  /** Achivements */
  ACHIEVEMENT_ONE_HUNRED_SCORE,
  ACHIEVEMENT_FIVE_HUNRED_SCORE,
  ACHIEVEMENT_ONE_THOUSAND_SCORE,
  
  /**Collide system*/
  ENTITY_IS_COLLIDING_WITH_FOOD
};

#endif // !SnakeGame_OBSERVER_EVENTS_HPP