#ifndef SnakeGame_SNAKE_STATES_CONTROLLER_HPP
#define SnakeGame_SNAKE_STATES_CONTROLLER_HPP
#include <unordered_map>
#include <memory>
#include <cassert>

#include "../ISnakeStates.hpp"
#include "SnakeStatesController.hpp"

class SnakeStatesController
{
private:
	using StateMapType = std::unordered_map<Uint32, std::shared_ptr<ISnakeStates>>;
public:
	SnakeStatesController();
	~SnakeStatesController();
	void InputHandler(const Snake_State &state);
	void update(EntityPosition &position_to_update, SquareType **map_state);
	void render();

public:
/**
 * @brief Adds state to the map
 * @return id of added state
*/
	unsigned int AddState(std::shared_ptr<ISnakeStates> state, Snake_StateType type);
	void RemoveState(Snake_StateType type);
	void TransitionTo(Snake_StateType type);

private:
	StateMapType m_StateMap;
	std::shared_ptr<ISnakeStates> m_CurrState;
	unsigned int m_size = 0;
};
#endif // !SnakeGame_SnakeStatesController_HPP
