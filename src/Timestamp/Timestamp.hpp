#ifndef SnakeGame_TIMER_HPP
#define SnakeGame_TIMER_HPP
#include <chrono>
#include <iostream>

namespace Utils{
class Timestamp {
 public:
  Timestamp() { m_start = std::chrono::high_resolution_clock::now(); };
  ~Timestamp() = default;
  void Start();
  void Stop();
  int64_t GetDurationInMs();
  double GetDurationInSeconds();

 private:
  std::chrono::_V2::system_clock::time_point m_start, m_end;
  std::chrono::duration<double> m_duration;
};

}; //! namespace
#endif  //! SnakeGame_TIMER_HPP
