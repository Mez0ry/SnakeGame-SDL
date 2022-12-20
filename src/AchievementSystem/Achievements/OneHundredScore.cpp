#include "OneHundredScore.hpp"

OneHundredScore::OneHundredScore() : m_isUnlocking(false) , m_isUnlocked(false)
{
  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "Achievements" + symbol + "one_hundred_score_achievement.png";

  m_AchievementTexture.LoadTexture(texture_path);

  m_AchievementTexture.set_dstRect(0, 0, 400, 125);
  m_AchievementTexture.set_srcRect(0, 0, 527, 125);
  m_Position.y = CAppSettings::instance().get_WindowHeight();

  m_AnimationStages.reserve(3);
  for (short int i = 0; i < 3; i++)
  {
    m_AnimationStages.push_back(false);
  }
  m_Seconds = -1;
}

OneHundredScore::~OneHundredScore()
{
  
}

void OneHundredScore::Update()
{
  //Show achievement
  if (m_AnimationStages[0] == false && m_Position.y > CAppSettings::instance().get_WindowHeight() - 150)
  {
    m_Position.x = 200;
    m_Position.y -= 10;
    if(m_Position.y <= CAppSettings::instance().get_WindowHeight() - 150){
      m_AnimationStages[0] = true;
    }
  }
  
  //Achievement delay before sliding back
 if (m_AnimationStages[0] == true && m_AnimationStages[1] == false){
   m_Seconds++;
   if(m_Seconds > 50){
     m_AnimationStages[1] = true;
   }
 }

  //Achievement sliding back
  if (m_AnimationStages[1] == true && m_AnimationStages[2] == false && m_Position.y < CAppSettings::instance().get_WindowHeight() + 100)
  {
    m_Position.y += 10;
    if(m_Position.y >= CAppSettings::instance().get_WindowHeight() + 100){
       m_AnimationStages[2] = true;
       m_isUnlocked = true;
    }
  }
 
}

void OneHundredScore::Render()
{
    m_AchievementTexture.set_TextureAlphaMod(230);
    m_AchievementTexture.set_dstRect(200, m_Position.y, 527, 125);
    m_AchievementTexture.RenderTexture();

    m_AchievementTexture.DestroyTexture();
    m_AchievementTexture.ReloadTexture();
}