#include "Timer.hpp"

Timer::~Timer()
{

}

void Timer::Start()
{
  m_start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;
  auto value = std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
}

int64_t Timer::GetDurationInMs()
{
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;

  auto value = std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
  return value.count();
}

double Timer::GetDurationInSeconds()
{
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;
  
  return m_duration.count();
}