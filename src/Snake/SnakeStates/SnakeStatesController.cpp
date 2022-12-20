#include "SnakeStatesController.hpp"

SnakeStatesController::SnakeStatesController()
{
	m_size = 0;
}

SnakeStatesController::~SnakeStatesController()
{
}

void SnakeStatesController::InputHandler(const Snake_State& state) {
    if (m_CurrState != nullptr)
	{
		m_CurrState->InputHandler(state);
	}
}

void SnakeStatesController::update(EntityPosition &position_to_update, SquareType **map_state)
{
	if (m_CurrState != nullptr)
	{
		m_CurrState->Update(position_to_update, map_state);
	}
}

void SnakeStatesController::render()
{
	if (m_CurrState != nullptr)
	{
		m_CurrState->Render();
	}
}

unsigned int SnakeStatesController::AddState(std::shared_ptr<ISnakeStates> state,Snake_StateType type)
{
	m_StateMap.insert(std::make_pair(type, std::move(state)));
	m_size++;
	return type;
}

void SnakeStatesController::RemoveState(Snake_StateType type)
{
	StateMapType::iterator it = m_StateMap.find(type);
	if (it != m_StateMap.end())
	{
		m_StateMap.erase(it);
		m_size--;
	}
}

void SnakeStatesController::TransitionTo(Snake_StateType type)
{
	StateMapType::iterator it = m_StateMap.find(type);
	if (it != m_StateMap.end())
	{
		if (m_CurrState != nullptr)
		{
			m_CurrState = nullptr;
		}

		m_CurrState = it->second;
	}
}