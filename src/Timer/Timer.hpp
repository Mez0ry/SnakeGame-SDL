#ifndef SnakeGame_TIMER_HPP
#define SnakeGame_TIMER_HPP
#include <chrono>
#include <iostream>

#define COLOR_CYAN "\e[0;36m"

enum TimeUnit{
 SECONDS,MILLISECONDS
};

class Timer {
  private:
  bool m_RAIItimer = false;
 public:
  Timer() : m_RAIItimer(false) { };
  Timer(const char* log_name);

  void Start();
  void Stop();
  int64_t GetDurationInMs();
  int64_t GetDurationInSeconds();
  
  void SetLogName(const char* log_name) { m_LogName = log_name; }
  ~Timer();

 private:
  std::chrono::_V2::system_clock::time_point m_start, m_end;
  std::chrono::duration<double> m_duration;
  const char* m_LogName;
};

#endif  //! SnakeGame_TIMER_HPP
