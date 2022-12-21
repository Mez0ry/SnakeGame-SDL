#ifndef SnakeGame_SNAKE_HPP
#define SnakeGame_SNAKE_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Map.hpp"
#include "ISnakeStates.hpp"
#include "SDL2/SDL.h"
/**SnakeStates*/
#include "SnakeStates/IdleState.hpp"
#include "SnakeStates/MovingState.hpp"
/**SnakeStates Controller*/
#include "SnakeStates/SnakeStatesController.hpp"
/** SnakeBody*/
#include "SnakeBody.hpp"

#include "../SpriteAnimation/SpriteAnimation.hpp"

class Snake : public Entity {
private:
  SquareType **m_MapState;
  EntityPosition m_SnakePosition;
  Snake_State m_SnakeState;
  SnakeStatesController m_SnakeStatesController;

public:
  Snake();
  ~Snake();

  void OnCreate();
  void OnDestroy();

  void InputHandler();
  void Update();
  void Render();

  bool isPlayer() const override { return true; }

  void set_MapState(SquareType **map_state) { this->m_MapState = map_state; }
  Snake_State &get_SnakeState() { return m_SnakeState; }
  const EntityPosition &get_PositionOnMap() const override {return m_SnakePosition;}

private:
  SDL_Event m_event;
  SnakeBody m_SnakeBody;
};
#endif //! SnakeGame_SNAKE_HPP