set(SNAKE_HEADERS Snake.hpp SnakeBody.hpp)
set(SNAKE_SOURCES Snake.cpp SnakeBody.cpp)

add_library(Snake SHARED ${SNAKE_HEADERS} ${SNAKE_SOURCES})