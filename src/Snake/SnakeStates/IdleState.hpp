#ifndef SnakeGame_IDLE_STATE_HPP
#define SnakeGame_IDLE_STATE_HPP
#include "../ISnakeStates.hpp"
class IdleState : public ISnakeStates {
public:
  IdleState();
  ~IdleState();

  void InputHandler(const Snake_State &state) override;
  void Update(EntityPosition &position_to_update,SquareType **map_state) override;
  void Render() override;

private:
  TextureManager m_Texture;
};
#endif // !SnakeGame_IDLE_STATE_HPP
