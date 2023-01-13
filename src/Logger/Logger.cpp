#include "Logger.hpp"

Logger *Logger::p_instance = 0;
LoggerDestroyer Logger::destroyer;

LoggerDestroyer::~LoggerDestroyer() { delete p_instance; }

void LoggerDestroyer::initialize(Logger *p) { p_instance = p; }

Logger &Logger::GetLogger() {
  if (!p_instance) {
    p_instance = new Logger();
    destroyer.initialize(p_instance);
  }
  return *p_instance;
}
