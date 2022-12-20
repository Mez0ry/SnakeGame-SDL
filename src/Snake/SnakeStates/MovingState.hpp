#ifndef SnakeGame_MOVING_DOWN_STATE_HPP
#define SnakeGame_MOVING_DOWN_STATE_HPP
#include "../ISnakeStates.hpp"

class MovingState : public ISnakeStates {
public:
  MovingState();
  ~MovingState();

  void InputHandler(const Snake_State &state) override;
  void Update(EntityPosition &position_to_update,SquareType **map_state) override;
  void Render() override;

private:
  enum class internal_sizes { MAX_TEXTURE = 4 };
  TextureManager m_Texture[static_cast<int>(internal_sizes::MAX_TEXTURE)];
  unsigned int m_TextureDrawIndex = 0;
};
#endif // !SnakeGame_MOVING_DOWN_STATE_HPP
