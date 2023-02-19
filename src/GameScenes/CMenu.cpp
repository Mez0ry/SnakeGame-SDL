#include "CMenu.hpp"

CMenu::CMenu()
{
  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  const std::string& src_folder = CAppSettings::instance().get_SourceFolder() + symbol;
  std::string load_path = src_folder + "assets" + symbol + "fonts" + symbol + "HACKED.ttf";

  int font_size = 50;
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].LoadFont(load_path.c_str(), font_size);
  }
  
  m_SoundManager.AddSound(SoundManagerModel(src_folder + "assets" + symbol + "Sound" + symbol + "confirm_style_2_002.wav","confirm_style_2_002"));
  m_SoundManager.AddSound(SoundManagerModel(src_folder + "assets" + symbol + "Sound" + symbol + "cursor_style_1.wav","cursor_style_1"));
}

CMenu::~CMenu()
{
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].DestroyText();
  }
}

void CMenu::OnCreate()
{
  m_MenuText[0].LoadText(m_labels[0], m_color[0]);
  m_MenuText[0].set_Rect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2 - 90, 130, 100);

  m_MenuText[1].LoadText(m_labels[1], m_color[0]);
  m_MenuText[1].set_Rect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2, 130, 100);

  m_MenuText[2].LoadText(m_labels[2], m_color[0]);
  m_MenuText[2].set_Rect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2 + 90, 130, 100);
}

void CMenu::BeforeDestruction()
{
  
}

void CMenu::OnDestroy()
{
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].DestroyText();
  }
  
}

void CMenu::InputHandler()
{
  if (SDL_PollEvent(&m_event))
  {
    Vec2 cursor_pos;
    cursor_pos.x = m_event.motion.x;
    cursor_pos.y = m_event.motion.y;
    switch (m_event.type)
    {
    case SDL_QUIT:
    {

      break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      for (int label_index = 0; label_index < 3; label_index++)
      {
        if (m_event.button.button == SDL_BUTTON_LEFT && m_MenuText[label_index].CursorIsColliding(cursor_pos))
        {
          m_SoundManager["confirm_style_2_002"]->PlaySound();
          switch(label_index){
            case 0:{
              g_GameSceneType = GameSceneType::Playing;
              break;
            }
            case 1:{
              g_GameSceneType = GameSceneType::Stats;
              break;
            }
            case 2:{
              g_GameSceneType = GameSceneType::Exit;
              break;
            }
          }
        }
      }
      break;
    } // case: !SDL_MOUSEBUTTONDOWN
    case SDL_MOUSEMOTION:
    {
      for (int i = 0; i < 3; i++)
      {

        if (m_MenuText[i].CursorIsColliding(cursor_pos))
        {
          if (m_MenuText[i].isSelected())
          {
            m_SoundManager["cursor_style_1"]->PlaySound();
            m_MenuText[i].set_SelectStatus(false);
            m_MenuText[i].DestroyText();
            m_MenuText[i].LoadText(m_labels[i], m_color[1]);
          }
        }
        else
        {
          if (!m_MenuText[i].isSelected())
          {
            m_MenuText[i].set_SelectStatus(true);
            m_MenuText[i].DestroyText();
            m_MenuText[i].LoadText(m_labels[i], m_color[0]);
          }
        }
      } // case: !SDL_MOUSEMOTION
      break;
    }
    } // !switch
  }
}

void CMenu::Update()
{
  
}

void CMenu::Render()
{
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].RenderText();
  }
}