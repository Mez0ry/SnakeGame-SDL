set(SNAKE_HEADERS Snake.hpp SnakeBody.hpp SnakeModel.hpp)
set(SNAKE_SOURCES Snake.cpp SnakeBody.cpp)

include_directories({PROJECT_SOURCE_DIR}/SnakeCommands)

add_library(Snake SHARED ${SNAKE_HEADERS} ${SNAKE_SOURCES})