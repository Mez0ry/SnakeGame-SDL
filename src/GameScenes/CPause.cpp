#include "CPause.hpp"

CPause::CPause()
{
    const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
    std::string font_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "fonts" + symbol + "HACKED.ttf";

    m_PauseText.LoadFont(font_path.c_str(),50);
    m_PauseText.set_dstRect((CAppSettings::instance().get_WindowWidth() / 2) - 50, (CAppSettings::instance().get_WindowHeight() / 2 ) - 10, 130, 100);
    m_PauseText.LoadSurfaceAndTexture("Pause", {255, 255, 255, 255});
}

CPause::~CPause()
{

}

void CPause::OnCreate()
{
  const std::string& slash_symbol_ref = CAppSettings::instance().get_SlashSymbol();
  std::string background_texture_path = CAppSettings::instance().get_SourceFolder() + slash_symbol_ref + "assets" + slash_symbol_ref + "GameScenes" + slash_symbol_ref + "CPause" + slash_symbol_ref + "background.bmp";

  m_BackgroundTexture.DestroyTexture();
  m_BackgroundTexture.LoadTexture(background_texture_path, ImageType::BMP);

  m_BackgroundTexture.set_dstRect(0,0,CAppSettings::instance().get_WindowWidth(),CAppSettings::instance().get_WindowHeight());
  m_BackgroundTexture.set_srcRect(0,0,CAppSettings::instance().get_WindowWidth(),CAppSettings::instance().get_WindowHeight());
  m_BackgroundTexture.set_TextureAlphaMod(100);
}

void CPause::BeforeDestruction()
{
    
}

void CPause::OnDestroy()
{
 m_PauseText.DestroySurfaceAndTexture();
 m_BackgroundTexture.DestroyTexture();   
}

void CPause::InputHandler()
{
    if (SDL_PollEvent(&m_event))
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
        } // !SDL_KEYDOWN
        } //!switch
    }
}

void CPause::Update()
{
    
}

void CPause::Render()
{
   m_PauseText.RenderTextOnTopOfAnother(m_BackgroundTexture.get_Texture(), m_BackgroundTexture.get_srcRect(), m_BackgroundTexture.get_dstRect());
 
}