#include "GameScore.hpp"

GameScore::GameScore() : m_Score(99)
{
  std::string score_bar_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/Shared/ScoreBar.png");
  m_ScoreBarTexture.LoadTexture(score_bar_path);

  int win_w{CAppSettings::instance().get_WindowWidth()},win_h{CAppSettings::instance().get_WindowHeight()};

  TextureSize texture_size(win_w * 0.2,win_h * 0.03f);

  Vec2 score_bar_pos;
  score_bar_pos.x = win_w / 2 - (texture_size.GetWidth() / 2);
  score_bar_pos.y = (texture_size.GetHeight() / 2);

  m_ScoreBarTexture.SetRect(score_bar_pos,texture_size);

  m_ScoreBarTexture.SetRect<SourceRect>({0,0},TextureSize(341,47));

  std::string font_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/fonts/HACKED.ttf");

  m_ScoreText.LoadFont(font_path.c_str(), 20);

  TextureSize score_size(win_w * 0.1f, win_h * 0.02f);
  
  m_ScoreText->SetRect({score_bar_pos.x + score_size.GetWidth() / 2,score_bar_pos.y + score_size.GetHeight() / 2},score_size);
  m_ScoreText->SetRect<SourceRect>({0,0}, TextureSize(100, 40));
}

GameScore::~GameScore()
{
}

void GameScore::OnCreate() { m_Score = 99; }

void GameScore::OnDestroy()
{
  m_GamesScore.push_front(m_Score);

  std::string file_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/CMatchHistory-Data.cfg");
  
  Serializer ser;
  auto& node = ser["CMatchHistory-Data"];
  auto& score_property = node["Score"];
  
  int write_index = 0;
  
  for(auto it = m_GamesScore.begin(); it != m_GamesScore.end();it++,write_index++){
      score_property.SetAs<int>(*it,write_index);
  }
  
  Serializer::Serialize(ser,file_path);
}

void GameScore::OnResize()
{
  int win_w{},win_h{};
  SDL_GetWindowSize(CSDLContext::instance().get_window(),&win_w,&win_h);

  TextureSize texture_size(win_w * 0.2,win_h * 0.03f);

  Vec2 score_bar_pos;
  score_bar_pos.x = win_w / 2 - (texture_size.GetWidth() / 2);
  score_bar_pos.y = (texture_size.GetHeight() / 2);

  m_ScoreBarTexture.SetRect(score_bar_pos,texture_size);

  m_ScoreBarTexture.SetRect<SourceRect>({0,0},TextureSize(341,47));

  TextureSize score_size(win_w * 0.1f, win_h * 0.02f);
  
  m_ScoreText->SetRect({score_bar_pos.x + score_size.GetWidth() / 2,score_bar_pos.y + score_size.GetHeight() / 2},score_size);
  m_ScoreText->SetRect<SourceRect>({0,0}, TextureSize(100, 40));
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
  m_ScoreBarTexture.RenderTexture();
  std::string text = "Score: " + std::to_string(m_Score);
  m_ScoreText.LoadText(text.c_str(), m_ScoreColor);
  
  m_ScoreText.RenderText();
  m_ScoreText.Reset();
}

void GameScore::Subtract(int num) { m_Score -= num; }

void GameScore::Add(int num) { m_Score += num; }

void GameScore::onNotify(const Entity &entity, ObserverEvents event)
{
  switch (event)
  {
  case ENTITY_IS_COLLIDING_WITH_FOOD:
  {
    if (const Food *ptrFood = dynamic_cast<const Food *>(&entity);ptrFood != nullptr)
    {
      m_Score += ptrFood->GetPoints();
      const_cast<Food *>(ptrFood)->RespawnNewFood();
    }
    break;
  }
  }
}
