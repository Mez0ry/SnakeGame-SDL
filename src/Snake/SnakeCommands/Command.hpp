#ifndef SNAKE_GAME_COMMAND_HPP
#define SNAKE_GAME_COMMAND_HPP
#include "../SnakeModel.hpp"

class Command {
public:
  virtual ~Command() {}
  virtual void Execute(SnakeModel &model) = 0;
};
#endif //! SNAKE_GAME_COMMAND_HPP