#ifndef SnakeGame_ISNAKE_STATES_HPP
#define SnakeGame_ISNAKE_STATES_HPP
#include "../Map.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../GameScenes/GameScene.hpp"
/** Entity base class*/
#include "../Entity/Entity.hpp"

typedef enum
{
  SNAKE_MOVING_STATE = 0x200,
  SNAKE_IDLE_STATE = 0x202,
  SNAKE_GROW_STATE = 0x204
} Snake_StateType;

enum class MoveDir : Uint8
{
  LEFT,
  RIGHT,
  UP,
  DOWN
};

typedef struct Moving
{
  Uint32 type; /**< ::Moving */
  MoveDir move_dir;
} Moving;

typedef struct Idle{
 Uint32 type; /**< ::Idle */
}Idle;

typedef struct Grow{
 Uint32 type; /**< ::Grow */
}Grow;

typedef union Snake_State
{
  Uint32 type; /**< State type, shared with all states */
  Moving moving;
  Idle idle;
  Grow grow;
} Snake_State;

class ISnakeStates
{
public:
  virtual ~ISnakeStates() {}
  virtual void InputHandler(const Snake_State &state) = 0;
  virtual void Update(EntityPosition &position_to_update, SquareType **map_state) = 0;
  virtual void Render() = 0;

protected:
  SquareType **m_MapState;
  EntityPosition m_SnakePosition;
  EntityPosition m_SnakePrevPosition;
  Snake_State m_SnakeState;
  bool EntIsOutOfMap();
};

inline bool ISnakeStates::EntIsOutOfMap()
{
  return (m_SnakePosition.y >= CAppSettings::instance().get_MapHeight() ||
          m_SnakePosition.x >= CAppSettings::instance().get_MapWidth() ||
          m_SnakePosition.y <= -1 || m_SnakePosition.x <= -1);
}
#endif //! SnakeGame_ISNAKE_STATES_HPP