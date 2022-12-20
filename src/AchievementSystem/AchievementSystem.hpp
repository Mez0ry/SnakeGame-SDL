#ifndef SnakeGame_ACHIEVEMENT_SYSTEM_HPP
#define SnakeGame_ACHIEVEMENT_SYSTEM_HPP
#include "../Observer/Observer.hpp"

#include <unordered_map>
#include <iostream>
#include <variant>
#include <vector>

#include "AchievementSettings/AchievementSettings.hpp"

class AchievementSystem : public Observer {
  private: 
  using AchievementMapType = std::unordered_map<ObserverEvents,bool>;
public:
  AchievementSystem();
  ~AchievementSystem();

  void Update();
  void Render();
  
  void onNotify(const Entity &entity, ObserverEvents event) override;
private:
  std::vector<AchievementInternal::var_t> m_AchievementsVec;
  OneHundredScore m_OneHundredScore; 
  FiveHundredScore m_FiveHundredScore;
  OneThousandScore m_OneThousandScore;
  AchievementSettings m_AchievementSettings;
};
#endif //! SnakeGame_ACHIEVEMENT_SYSTEM_HPP