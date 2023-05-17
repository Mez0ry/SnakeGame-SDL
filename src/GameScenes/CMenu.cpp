#include "CMenu.hpp"

CMenu::CMenu()
{
  const std::string& src_folder = CAppSettings::instance().get_SourceFolder();
  std::string load_path = src_folder + CAppSettings::GetCorrectedPath("/assets/fonts/HACKED.ttf");

  int font_size = 50;

  for(auto& text : m_MenuText){
     text.LoadFont(load_path.c_str(), font_size);
  }
  
  m_SoundManager.AddSound(SoundManagerModel(src_folder + CAppSettings::GetCorrectedPath("/assets/Sound/confirm_style_2_002.wav"),"confirm_style_2_002"));
  m_SoundManager.AddSound(SoundManagerModel(src_folder + CAppSettings::GetCorrectedPath("/assets/Sound/cursor_style_1.wav"),"cursor_style_1"));
}

CMenu::~CMenu()
{
  for (auto& text : m_MenuText)
  {
    text.Reset();
  }
}

void CMenu::OnCreate()
{
  SDL_SetRenderDrawColor(CSDLContext::instance().get_renderer(),94,73,145,255);
  
  TextureSize texture_size(130, 100);
  for(int i = 0, y_offset = -90;i < 3;i++,y_offset += 90){
    Vec2 new_pos;
    new_pos.x = (CAppSettings::instance().get_WindowWidth() / 2) - (texture_size.GetWidth() / 2);
    new_pos.y = (CAppSettings::instance().get_WindowHeight() / 2) + y_offset;

    m_MenuText[i].LoadText(m_labels[i], m_color[0]);
    m_MenuText[i]->SetRect(new_pos, texture_size);
    m_MenuText[i]->SetRect<SourceRect>({0,0}, texture_size);
  }
}

void CMenu::OnDestroy()
{
  for (auto& text : m_MenuText)
  {
    text.Reset();
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
      int label_index = 0;
      for (auto& text : m_MenuText)
      {
        if (m_event.button.button == SDL_BUTTON_LEFT && text->PointIsOnTexture(cursor_pos))
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
        label_index++;
      }
      break;
    } // case: !SDL_MOUSEBUTTONDOWN
    case SDL_MOUSEMOTION:
    {
      int label_index = 0;
      for (auto& text : m_MenuText)
      {

        if (text->PointIsOnTexture(cursor_pos))
        {
            m_SoundManager["cursor_style_1"]->PlaySound(); 
            text.Reset();
            text.LoadText(m_labels[label_index], m_color[1]);
        }
        else
        {
            text.Reset();
            text.LoadText(m_labels[label_index], m_color[0]);
        }

        label_index++;
      } // case: !SDL_MOUSEMOTION
      break;
    }

    case SDL_WINDOWEVENT:{
      switch(m_event.window.event){
          case SDL_WINDOWEVENT_RESIZED:{
              Resize();
              break;
          }
      }
      break;
    }//! SDL_WINDOW_EVENT

    } // !switch
  }
}

void CMenu::Update(float dt)
{
  
}

void CMenu::Render()
{
  for (auto& text : m_MenuText)
  {
    text.RenderText();
  }
}

void CMenu::Resize()
{
  int win_w{},win_h{};
  SDL_GetWindowSize(CSDLContext::instance().get_window(),&win_w,&win_h);

  int half_width = (win_w / 2);
  int half_height = (win_h / 2);

  int y_offset = -90;

  for(auto& text : m_MenuText){
    text->SetTexturePosition({half_width - (text->GetTextureSize().GetWidth() / 2),half_height - (text->GetTextureSize().GetHeight() / 2) + y_offset});
    y_offset += 90;
  }

}