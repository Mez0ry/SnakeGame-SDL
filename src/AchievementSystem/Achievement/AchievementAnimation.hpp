#ifndef SnakeGame_ACHIEVEMENT_ANIMATION_HPP
#define SnakeGame_ACHIEVEMENT_ANIMATION_HPP
#include "../../CAppSettings/CAppSettings.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <functional>
#include <queue>
#include <memory>
#include "../../Timestamp/Timestamp.hpp"

class Task{
public:
 virtual ~Task() {}
 virtual bool isTimedTask() const = 0;
};

class RectangleTask : public Task{
public:
virtual bool execute(SDL_Rect& rect) = 0;
bool isTimedTask() const override {return false;}
};

class AchievementTask : public RectangleTask{
protected:
 std::function<bool(SDL_Rect &rect)> m_Operation;

public:
  AchievementTask(std::function<bool(SDL_Rect &rect)> operation)
      : m_Operation(operation) {}
  
  virtual ~AchievementTask() {}
 
  /**
   * @return True on success otherwise false
  */
  bool execute(SDL_Rect& rect) override{
    return (m_Operation(rect)) ? true : false;
  }
};

class TimedTask : public Task{
public:
virtual bool execute() = 0;
virtual bool isTimedTask() const {return true;}
};

class DelayedTask : public TimedTask {
private:
 double m_offset;
 double m_delay;

public:
   
 explicit DelayedTask(uint32_t iterations) : m_delay((double)iterations),m_offset(1) {

  }

  ~DelayedTask(){}

  bool execute() override{
    m_delay -= m_offset;
    if(m_delay < 0.005){
      return true;
    }
    return false;
  }
};

class AchievementAnimation {
public:
  AchievementAnimation() {}
  virtual ~AchievementAnimation() {}

  virtual void Update(SDL_Rect& texture) = 0;
  virtual bool isUnlocked() const = 0;
  virtual void set_isUnlocked(bool is_unlocked) = 0;

private:
};

class DefaultAnimation : public AchievementAnimation {
public:
  DefaultAnimation() : m_IsUnlocked(false) {
    
    // show achievement
    auto show_achievement = [&](SDL_Rect &rect) -> bool {
      if (rect.y > CAppSettings::instance().get_WindowHeight() - 150) {
        rect.y -= 10;
      } else {
        return true;
      }
      return false;
    };

    m_TaskQueue.push(std::make_shared<AchievementTask>(AchievementTask(show_achievement)));

    m_TaskQueue.push(std::make_shared<DelayedTask>(DelayedTask(100)));

    // Achievement sliding back
    auto achievement_sliding_back = [&](SDL_Rect &rect) -> bool {
      if (rect.y < CAppSettings::instance().get_WindowHeight() + 100) {
        rect.y += 10;
      } else {
        return true;
      }
      return false;
    };

    m_TaskQueue.push(std::make_shared<AchievementTask>(AchievementTask(achievement_sliding_back)));
  }

  ~DefaultAnimation() {}

  void Update(SDL_Rect& rect) override {
    if (m_TaskQueue.empty() || m_IsUnlocked)
      return;

    if(m_TaskQueue.front()->isTimedTask()){
        TimedTask* pTimed_task = dynamic_cast<TimedTask*>(m_TaskQueue.front().get());
      if(pTimed_task != nullptr && pTimed_task->execute()){
        m_TaskQueue.pop();
      }

    }else{
     RectangleTask* pRectangle_task = dynamic_cast<RectangleTask*>(m_TaskQueue.front().get());
    if (pRectangle_task != nullptr && pRectangle_task->execute(rect)) {
      m_TaskQueue.pop();
    }

    }
    if (m_TaskQueue.empty())
      m_IsUnlocked = true;
  }

  bool isUnlocked() const override { return m_IsUnlocked; }
  void set_isUnlocked(bool is_unlocked) override { m_IsUnlocked = is_unlocked; }

private:
  std::queue<std::shared_ptr<Task>> m_TaskQueue;
  bool m_IsUnlocked;
};

#endif //! SnakeGame_ACHIEVEMENT_ANIMATION_HPP