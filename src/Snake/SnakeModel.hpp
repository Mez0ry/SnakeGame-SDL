#ifndef SnakeGame_SNAKE_MODEL_HPP
#define SnakeGame_SNAKE_MODEL_HPP
#include <cstdint>
#include "../Texture/Texture.hpp"
#include "../Entity/Entity.hpp"

enum class MoveDir : uint8_t
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  UNKNOWN
};

struct SnakeModel{
  EntityPosition m_SnakePosition;
  EntityPosition m_PrevSnakePosition;
  Texture m_SnakeTextures[4];
  int m_TextureDrawIndex = -1;
};

#endif //!SnakeGame_SNAKE_MODEL_HPP