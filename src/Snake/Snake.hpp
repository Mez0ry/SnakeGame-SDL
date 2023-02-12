#ifndef SnakeGame_SNAKE_HPP
#define SnakeGame_SNAKE_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Map.hpp"
#include "SDL2/SDL.h"
#include "SnakeModel.hpp"

/** SnakeBody*/
#include "SnakeBody.hpp"

#include "SnakeCommands/MoveTo.hpp"


class Snake : public Entity {
private:
  SquareType **m_MapState;
public:
  Snake();
  ~Snake();

  void OnCreate();
  void OnDestroy();

  void InputHandler();
  void Update();
  void Render();

  bool isPlayer() const override { return true; }

  void set_MapState(SquareType **map_state) { this->m_MapState = map_state; m_MoveToCommand.set_MapState(map_state); }
  void set_MoveDir(MoveDir dir) {
    m_MoveDir = dir;
  }

  void GrowBody(){
    m_SnakeBody.AddLength();
  }

  const EntityPosition &get_PositionOnMap() const override {return m_Model.m_SnakePosition;}
private:
  SnakeBody m_SnakeBody;
  SnakeModel m_Model;
  MoveDir m_MoveDir;
  MoveTo m_MoveToCommand;
};
#endif //! SnakeGame_SNAKE_HPP