set(SNAKE_STATES_HEADERS SnakeStates/IdleState.hpp SnakeStates/MovingState.hpp SnakeStates/SnakeStatesController.hpp)
set(SNAKE_STATES_SOURCES SnakeStates/IdleState.cpp SnakeStates/MovingState.cpp SnakeStates/SnakeStatesController.cpp)

set(SNAKE_HEADERS ISnakeStates.hpp Snake.hpp SnakeBody.hpp)
set(SNAKE_SOURCES Snake.cpp SnakeBody.cpp)

add_library(Snake SHARED ${SNAKE_STATES_HEADERS} ${SNAKE_STATES_SOURCES} ${SNAKE_HEADERS} ${SNAKE_SOURCES})