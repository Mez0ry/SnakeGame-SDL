#ifndef SNAKE_GAME_MOVE_TO_COMMAND_HPP
#define SNAKE_GAME_MOVE_TO_COMMAND_HPP
#include "Command.hpp"
#include "../../Map.hpp"

class MoveTo : public Command {
private:
  MoveDir m_dir;
  SquareType **m_MapState;

public:
  MoveTo() = default;
  ~MoveTo() = default;
  
  void set_MapState(SquareType** map_state){
    m_MapState = map_state;
  }
  void SetDir(MoveDir dir) {m_dir = dir;}

  virtual void Execute(SnakeModel &model) {
    if(m_dir == MoveDir::UNKNOWN){
      return;
    }

    model.m_PrevSnakePosition = model.m_SnakePosition;
    switch (m_dir) {
    case MoveDir::LEFT: {
      model.m_TextureDrawIndex = 0;
      model.m_SnakePosition.x -= 1;
      break;
    }
    case MoveDir::RIGHT: {
      model.m_TextureDrawIndex = 1;
      model.m_SnakePosition.x += 1;
      break;
    }
    case MoveDir::UP: {
      model.m_TextureDrawIndex = 2;
      model.m_SnakePosition.y -= 1;
      break;
    }
    case MoveDir::DOWN: {
      model.m_TextureDrawIndex = 3;
      model.m_SnakePosition.y += 1;
      break;
    }
    } //! switch

    model.m_SnakeTextures[model.m_TextureDrawIndex].set_dstRect(MapUtils::CorrectWidthPosOnTheMap(model.m_SnakePosition.x),MapUtils::CorrectHeightPosOnTheMap(model.m_SnakePosition.y), TextureConstants::TextureWidth, TextureConstants::TextureHeight);

    if (SnakeIsOutOfMap(model)) {
      g_GameSceneType = GameSceneType::Menu;
      return;
    }

    m_MapState[model.m_PrevSnakePosition.y][model.m_PrevSnakePosition.x] =SquareType::BACKGROUND;

    m_MapState[model.m_SnakePosition.y][model.m_SnakePosition.x] = SquareType::ENTITY;
  }

private:
  inline bool SnakeIsOutOfMap(SnakeModel& model) {
    return (model.m_SnakePosition.y >= CAppSettings::instance().get_MapHeight() || model.m_SnakePosition.x >= CAppSettings::instance().get_MapWidth() || model.m_SnakePosition.y <= -1 || model.m_SnakePosition.x <= -1);
  }
};
#endif //! SNAKE_GAME_MOVE_TO_COMMAND_HPP