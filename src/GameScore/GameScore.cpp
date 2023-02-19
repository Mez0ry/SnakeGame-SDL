#include "GameScore.hpp"

GameScore::GameScore() : m_Score(99)
{
  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();

  std::string font_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "HACKED.ttf";

  m_FontManager.LoadFont(font_path.c_str(), 20);

  m_FontManager.set_Rect(50, CAppSettings::instance().get_WindowHeight() - 50, 100, 40);

  std::string map_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "map" + symbol + "map_texture.png";
  m_BackTexture.LoadTexture(map_texture_path);
}

GameScore::~GameScore()
{
}

void GameScore::OnCreate() { m_Score = 99; }

void GameScore::OnDestroy()
{
  m_GamesScore.push_front(m_Score);

  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string file_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "CMatchHistory-Data.cfg";
  
  Serializer ser;
  auto& node = ser["CMatchHistory-Data"];
  auto& score_property = node["Score"];
  
  int write_index = 0;
  
  for(auto it = m_GamesScore.begin(); it != m_GamesScore.end();it++,write_index++){
      score_property.set_Int(*it,write_index);
  }
  
  Serializer::Serialize(ser,file_path);
}

void GameScore::Update()
{
  EntityNull entity_null_object;
  if (m_Score >= 100 && m_Score <= 115)
  {
    Notify(entity_null_object, ACHIEVEMENT_ONE_HUNRED_SCORE);
  }
  else if (m_Score >= 500 && m_Score <= 515)
  {
    Notify(entity_null_object, ACHIEVEMENT_FIVE_HUNRED_SCORE);
  }
  else
  {
    if (m_Score >= 1000 && m_Score <= 1015)
    {
      Notify(entity_null_object, ACHIEVEMENT_ONE_THOUSAND_SCORE);
    }
  }
}

void GameScore::Render()
{
  std::string text = "Score: " + std::to_string(m_Score);
  m_FontManager.LoadText(text.c_str(), m_ScoreColor);

  m_FontManager.RenderTextOnTopOfAnother(m_BackTexture.get_Texture(), m_BackTexture.get_Rect<SourceRect>(), m_BackTexture.get_Rect());

  m_FontManager.DestroyText();
}

void GameScore::Subtract(int num) { m_Score -= num; }

void GameScore::Add(int num) { m_Score += num; }

void GameScore::onNotify(const Entity &entity, ObserverEvents event)
{
  switch (event)
  {
  case ENTITY_IS_COLLIDING_WITH_FOOD:
  {
    if (const Food *ptrFood = dynamic_cast<const Food *>(&entity);
        ptrFood != nullptr)
    {
      if (ptrFood->get_FoodType() == FoodType::Edible)
      {
        m_Score += ptrFood->get_PointsForFood();
      }
      else
      {
        if (ptrFood->get_FoodType() == FoodType::InEdible)
        {
          m_Score -= ptrFood->get_PointsForFood();
        }
      }
      const_cast<Food *>(ptrFood)->RespawnNewFood();
    }
    break;
  }
  }
}
