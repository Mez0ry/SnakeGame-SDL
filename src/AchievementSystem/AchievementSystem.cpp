#include "AchievementSystem.hpp"

AchievementSystem::AchievementSystem() {
  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string achievement_dir_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "Achievements";

  int achievement_posX = CAppSettings::instance().get_WindowWidth() / 4;
  int achievement_posY = CAppSettings::instance().get_WindowHeight();

  std::filesystem::path path;
  std::string file_extension;
  std::string file_name;

  for (auto &dirEntry : recursive_directory_iterator(achievement_dir_path)) {
    path           = dirEntry.path();
    file_extension = path.extension();
    file_name      = path.filename();
    file_name      = file_name.substr(0, file_name.find_last_of("."));

    m_AchievesMap.insert(std::make_pair(file_name, std::make_shared<Achievement>()));
    m_AchievesMap.at(file_name)->LoadTexture( path.string(), 527, 125);
    m_AchievesMap.at(file_name)->AddAnimation( std::make_unique<DefaultAnimation>());
  
    m_AchievesMap.at(file_name)->SetAchievementAlphaMod(230);

    m_AchievesMap.at(file_name)->set_dstRect(achievement_posX, achievement_posY,  527, 125);
  }

  std::string achievement_config_path = CAppSettings::instance().get_SourceFolder() + symbol + "AchievementSystem" + symbol + "Achievement" + symbol + "config" + symbol + "achieve_config.cfg";

  Serializer des;
  if(Serializer::Deserialize(des,achievement_config_path)){
    for(auto key : m_AchievesMap){

      auto& node = des[key.first];
      auto& unlocked_property = node["Unlocked"];
      key.second->set_isUnlocked(unlocked_property.get_Bool(0));
    }
  }
  
}

AchievementSystem::~AchievementSystem() {
   const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
   std::string achievement_config_path = CAppSettings::instance().get_SourceFolder() + symbol + "AchievementSystem" + symbol + "Achievement" + symbol + "config" + symbol + "achieve_config.cfg";

    Serializer ser;
    for (auto &key : m_AchievesMap) {
      auto &node = ser[key.first];
      auto &unlocked_property = node["Unlocked"];
      unlocked_property.set_Bool(key.second->isUnlocked());
    }

    Serializer::Serialize(ser, achievement_config_path);
}

void AchievementSystem::Update() {
  if (m_CurrentAchieveProccessing.empty())
    return;

  m_CurrentAchieveProccessing.front()->Update();
  if (m_CurrentAchieveProccessing.front()->isUnlocked()) {
    m_CurrentAchieveProccessing.pop();
  }
}

void AchievementSystem::Render() {
  if (m_CurrentAchieveProccessing.empty())
    return;

  m_CurrentAchieveProccessing.front()->Render();
  if (m_CurrentAchieveProccessing.front()->isUnlocked()) {
    m_CurrentAchieveProccessing.pop();
  }
}

void AchievementSystem::onNotify(const Entity &entity, ObserverEvents event) {
  if (m_AchievesMap.empty())
    return;

  switch (event) {
  case ACHIEVEMENT_ONE_HUNRED_SCORE: {
    if (m_AchievesMap["one_hundred_score_achievement"].use_count() < 2)
        m_CurrentAchieveProccessing.push(m_AchievesMap["one_hundred_score_achievement"]);
    break;
  }
  case ACHIEVEMENT_FIVE_HUNRED_SCORE: {
      if (m_AchievesMap["five_hundred_score_achievement"].use_count() < 2)
        m_CurrentAchieveProccessing.push(m_AchievesMap["five_hundred_score_achievement"]);
    
    break;
  }
  case ACHIEVEMENT_ONE_THOUSAND_SCORE: {
   if (m_AchievesMap["one_thousand_score_achievement"].use_count() < 2)
        m_CurrentAchieveProccessing.push(m_AchievesMap["one_thousand_score_achievement"]);
    break;
  }
  }
}
