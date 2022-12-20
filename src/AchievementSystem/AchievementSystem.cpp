#include "AchievementSystem.hpp"
AchievementSystem::AchievementSystem() {
 m_AchievementsVec.push_back(std::move(m_OneHundredScore));
 m_AchievementsVec.push_back(std::move(m_FiveHundredScore));
 m_AchievementsVec.push_back(std::move(m_OneThousandScore));

 m_AchievementSettings.ParseConfigFile(std::ref(m_AchievementsVec));
}

AchievementSystem::~AchievementSystem() {
    m_AchievementSettings.UpdateConfigAttribs(std::ref(m_AchievementsVec));
}

void AchievementSystem::Update() {
   for(std::vector<AchievementInternal::var_t>::iterator it = m_AchievementsVec.begin(); it != m_AchievementsVec.end();++it){
        std::visit([](auto && val){
            if(val.get_IsUnlocking() && !val.IsUnlocked()){
                val.Update();
            }
        },(*it));
   }
}

void AchievementSystem::Render() {
 for(std::vector<AchievementInternal::var_t>::iterator it = m_AchievementsVec.begin(); it != m_AchievementsVec.end();++it){
        std::visit([](auto && val){
            if(val.get_IsUnlocking() && !val.IsUnlocked()){
                val.Render();
            }
        },(*it));
   }
}

void AchievementSystem::onNotify(const Entity &entity, ObserverEvents event) {
  switch (event) {
  case ACHIEVEMENT_ONE_HUNRED_SCORE: {
    std::visit([](auto&& arg){arg.set_IsUnlocking(true);},m_AchievementsVec.at(ACHIEVEMENT_ONE_HUNRED_SCORE));
    break;
  }
  case ACHIEVEMENT_FIVE_HUNRED_SCORE: {
    std::visit([](auto&& arg){arg.set_IsUnlocking(true);},m_AchievementsVec.at(ACHIEVEMENT_FIVE_HUNRED_SCORE));
    break;
  }
  case ACHIEVEMENT_ONE_THOUSAND_SCORE: {
    std::visit([](auto&& arg){arg.set_IsUnlocking(true);},m_AchievementsVec.at(ACHIEVEMENT_ONE_THOUSAND_SCORE));
    break;
  }
  }
}
