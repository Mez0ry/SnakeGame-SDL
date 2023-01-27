#ifndef SnakeGame_ACHIEVEMENT_SYSTEM_HPP
#define SnakeGame_ACHIEVEMENT_SYSTEM_HPP
#include "../Observer/Observer.hpp"

#include <iostream>
#include <variant>
#include <unordered_map>
#include <filesystem>
#include <queue>
#include "Achievement/Achievement.hpp"
#include "../Serializer/Serializer.hpp"

class AchievementSystem : public Observer {
  private: 
  using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
public:
  AchievementSystem();
  ~AchievementSystem();

  void Update();
  void Render();
  
  void onNotify(const Entity &entity, ObserverEvents event) override;
private:
  std::unordered_map<std::string,std::shared_ptr<Achievement>> m_AchievesMap;
  std::queue<std::shared_ptr<Achievement>> m_CurrentAchieveProccessing;
};
#endif //! SnakeGame_ACHIEVEMENT_SYSTEM_HPP