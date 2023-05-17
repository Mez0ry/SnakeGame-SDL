#ifndef SnakeGame_TIMER_HPP
#define SnakeGame_TIMER_HPP
#include <chrono>
#include <iostream>
#include <cstdint>
#include "SDL2/SDL.h"

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

class SDL_Timer{
  public:
      SDL_Timer();
      ~SDL_Timer() = default;

      void Start();
      void Stop();
      void Pause();
      void UnPause();

      Uint32 GetTicks();

      //Checks the status of the timer
      bool isStarted();
      bool isPaused();

  private:
      //The clock time when the timer started
      Uint32 m_StartTicks;

      //The ticks stored when the timer was paused
      Uint32 m_PausedTicks;

      //The timer status
      bool m_IsPaused;
      bool m_IsStarted;
};

}; //! namespace
#endif  //! SnakeGame_TIMER_HPP
