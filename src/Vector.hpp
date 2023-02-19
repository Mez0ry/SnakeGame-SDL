#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

struct Vec2 {
  Vec2() = default;
  explicit Vec2(int pos_x, int pos_y) : x(pos_x), y(pos_y) {}
  ~Vec2() = default;

  int x, y;
};

#endif // __VECTOR_HPP__