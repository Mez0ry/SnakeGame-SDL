#include "Timestamp.hpp"

void Utils::Timestamp::Start() {
  m_start = std::chrono::high_resolution_clock::now();
}

void Utils::Timestamp::Stop() {
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;
  auto value =
      std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
}

int64_t Utils::Timestamp::GetDurationInMs() {
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;

  auto value =
      std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
  return value.count();
}

double Utils::Timestamp::GetDurationInSeconds() {
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;

  return m_duration.count();
}
namespace Utils {

SDL_Timer::SDL_Timer() {
  m_StartTicks = 0;
  m_PausedTicks = 0;

  m_IsPaused = false;
  m_IsStarted = false;
}

void SDL_Timer::Start() {
  m_IsStarted = true;

  // Unpause the timer
  m_IsPaused = false;

  // Get the current clock time
  m_StartTicks = SDL_GetTicks();
  m_PausedTicks = 0;
}

void SDL_Timer::Stop() {
  // Stop the timer
  m_IsStarted = false;

  // Unpause the timer
  m_IsPaused = false;

  // Clear tick variables
  m_StartTicks = 0;
  m_PausedTicks = 0;
}

void SDL_Timer::Pause() {
  if (m_IsStarted && !m_IsPaused) {
    // Pause the timer
    m_IsPaused = true;

    // Calculate the paused ticks
    m_PausedTicks = SDL_GetTicks() - m_StartTicks;
    m_StartTicks = 0;
  }
}
void SDL_Timer::UnPause() {
  if (m_IsStarted && m_IsPaused) {
    // Unpause the timer
    m_IsPaused = false;

    // Reset the starting ticks
    m_StartTicks = SDL_GetTicks() - m_PausedTicks;

    // Reset the paused ticks
    m_PausedTicks = 0;
  }
}

Uint32 SDL_Timer::GetTicks() {
  Uint32 time = 0;

  if (m_IsStarted) {
    if (m_IsPaused) {
      time = m_PausedTicks;
    } else {
      time = SDL_GetTicks() - m_StartTicks;
    }
  }

  return time;
}

bool SDL_Timer::isStarted() {return m_IsStarted;}

bool SDL_Timer::isPaused() {return m_IsPaused;}
} // namespace Utils