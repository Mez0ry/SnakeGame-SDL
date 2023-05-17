#include "CPause.hpp"

CPause::CPause()
{
    std::string font_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/fonts/HACKED.ttf");

    m_PauseText.LoadFont(font_path.c_str(),50);
    m_PauseText->SetRect({(CAppSettings::instance().get_WindowWidth() / 2) - 50, (CAppSettings::instance().get_WindowHeight() / 2 ) - 10}, TextureSize(130, 100));
    m_PauseText->SetRect<SourceRect>({0,0}, TextureSize(130, 100));
    m_PauseText.LoadText("Pause", {255, 255, 255, 255});
}

CPause::~CPause()
{

}

void CPause::OnCreate()
{
  std::string background_texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CPause/background.bmp");
  
  m_BackgroundTexture.Reset();
  m_BackgroundTexture.LoadTexture(background_texture_path);

  m_BackgroundTexture.SetRect({0,0},TextureSize(CAppSettings::instance().get_WindowWidth(),CAppSettings::instance().get_WindowHeight()));
  m_BackgroundTexture.SetRect<SourceRect>({0,0},TextureSize(CAppSettings::instance().get_WindowWidth(),CAppSettings::instance().get_WindowHeight()));
  
  SDL_SetTextureAlphaMod((*m_BackgroundTexture),100);
}

void CPause::OnDestroy()
{
 m_PauseText.Reset();
 m_BackgroundTexture.Reset();   
}

void CPause::InputHandler()
{
    while (SDL_PollEvent(&m_event))
    {
        switch (m_event.type)
        {
        case SDL_QUIT:
        {
            g_GameSceneType = GameSceneType::Exit;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
                g_GameSceneType = GameSceneType::Playing; 
                break;
            }
            }
            break;
        } // !SDL_KEYDOWN

        case SDL_WINDOWEVENT:{
            switch(m_event.window.event){
                case SDL_WINDOWEVENT_RESIZED:{
                    Resize();
                    break;
                }
            }
            break;
        }//! SDL_WINDOW_EVENT

        } //!switch
    }
}

void CPause::Update(float dt)
{
    
}

void CPause::Render()
{
    m_BackgroundTexture.RenderTexture();
    m_PauseText.RenderText();
}

void CPause::Resize()
{
    int win_w{},win_h{};
    SDL_GetWindowSize(CSDLContext::instance().get_window(),&win_w,&win_h);

    m_BackgroundTexture.SetRect<SourceRect>({0,0},TextureSize(win_w,win_h));
    m_BackgroundTexture.SetRect({0,0},TextureSize(win_w,win_h));
    m_PauseText->SetTexturePosition({(win_w / 2) - (m_PauseText->GetTextureSize().GetWidth() / 2),(win_h / 2) - (m_PauseText->GetTextureSize().GetHeight() / 2)});
}