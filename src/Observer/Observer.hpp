#ifndef SnakeGame_OBSERVER_HPP
#define SnakeGame_OBSERVER_HPP
#include "../Entity/Entity.hpp"
#include "ObserverEvents.hpp"
class Observer
{
public:
  virtual ~Observer() {}
  virtual void onNotify(const Entity& entity, ObserverEvents event) = 0;
};
#endif //!SnakeGame_OBSERVER_HPP