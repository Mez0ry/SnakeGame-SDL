#include "CMenu.hpp"

CMenu::CMenu()
{
  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string font_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "HACKED.ttf";

  int font_size = 50;
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].LoadFont(font_path.c_str(), font_size);
  }

  m_MenuText[0].AddChangeStateEventOnPress(GameSceneType::Playing);
  m_MenuText[1].AddChangeStateEventOnPress(GameSceneType::Stats);
  m_MenuText[2].AddChangeStateEventOnPress(GameSceneType::Exit);
}

CMenu::~CMenu()
{
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].DestroySurfaceAndTexture();
  }
}

void CMenu::OnCreate()
{
  m_MenuText[0].LoadSurfaceAndTexture(m_labels[0], m_color[0]);
  m_MenuText[0].set_dstRect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2 - 90, 130, 100);

  m_MenuText[1].LoadSurfaceAndTexture(m_labels[1], m_color[0]);
  m_MenuText[1].set_dstRect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2, 130, 100);

  m_MenuText[2].LoadSurfaceAndTexture(m_labels[2], m_color[0]);
  m_MenuText[2].set_dstRect(CAppSettings::instance().get_WindowWidth() / 2, CAppSettings::instance().get_WindowHeight() / 2 + 90, 130, 100);
}

void CMenu::BeforeDestruction()
{
  
}

void CMenu::OnDestroy()
{
  for (int i = 0; i < 3; i++)
  {
    m_MenuText[i].DestroySurfaceAndTexture();
  }
   SDL_FlushEvents(SDL_KEYDOWN,SDL_MOUSEWHEEL);
}

void CMenu::InputHandler()
{
  if (SDL_PollEvent(&m_event))
  {
    CursorPosition cursor_pos;
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
        if (m_event.button.button == SDL_BUTTON_LEFT &&
            m_MenuText[label_index].CursorIsColliding(cursor_pos))
        {
          m_MenuText[label_index].OnPress(&FontManager_internal::callback_ChangeSceneTo);
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
          if (!m_MenuText[i].isSelected())
          {
            m_MenuText[i].set_SelectStatus(true);
            m_MenuText[i].DestroySurfaceAndTexture();
            m_MenuText[i].LoadSurfaceAndTexture(m_labels[i], m_color[1]);
          }
        }
        else
        {
          if (m_MenuText[i].isSelected())
          {
            m_MenuText[i].set_SelectStatus(false);
            m_MenuText[i].DestroySurfaceAndTexture();
            m_MenuText[i].LoadSurfaceAndTexture(m_labels[i], m_color[0]);
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
    m_MenuText[i].RenderCopy();
  }
}