#include "Timer.hpp"

Timer::Timer(const char *log_name) : m_RAIItimer(true)
{
  m_LogName = log_name;
  m_start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
  if (m_RAIItimer)
  {
    m_end = std::chrono::high_resolution_clock::now();
    m_duration = m_end - m_start;
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
    std::cout << COLOR_CYAN << "[" << m_LogName << "]" << " " << value.count() << " " << "ms" << '\n';
  }
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
  std::cout << COLOR_CYAN << "[" << m_LogName << "]" << " " << value.count() << " " << "ms" << '\n';
}

int64_t Timer::GetDurationInMs()
{
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;

  auto value = std::chrono::duration_cast<std::chrono::milliseconds>(m_duration);
  return value.count();
}

int64_t Timer::GetDurationInSeconds()
{
  m_end = std::chrono::high_resolution_clock::now();
  m_duration = m_end - m_start;

  auto value = std::chrono::duration_cast<std::chrono::seconds>(m_duration);
  
  return value.count();
}

