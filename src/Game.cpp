#include "Game.hpp"

Game::Game() : m_bGameLoop(true)
{
  CSDLContext::instance().init();
  m_ScenesController.CollectScenes();
  m_ScenesController.TransitionTo(GameSceneType::Menu);

	std::string cursor_texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/Other/cursor/cursor_default.png");
  m_CustomCursor.LoadCursor(cursor_texture_path);
}

Game::~Game()
{

}

void Game::Run()
{
  //The frames per second timer
  Utils::SDL_Timer fps_timer;

  //The frames per second cap timer
  Utils::SDL_Timer cap_timer;

  Utils::SDL_Timer step_timer;

  int counted_frames = 0;
  fps_timer.Start();

  while (m_bGameLoop)
  {
    cap_timer.Start();
    
    SDL_RenderClear(CSDLContext::instance().get_renderer());
    
    InputHandler();
    float dt = step_timer.GetTicks() / 1000.0f;
    Update(dt * ((m_fps / 2) - 0.1f));
    step_timer.Start();
    
    Render();

    SDL_RenderPresent(CSDLContext::instance().get_renderer());

    ++counted_frames;

    if(g_GameSceneType != GameSceneType::Menu){
      int frame_ticks = cap_timer.GetTicks();
      if(m_frameDelay > frame_ticks)
      {
        //Wait remaining time
        SDL_Delay(m_frameDelay - frame_ticks);
      }
    }
    
    if(g_GameSceneType == GameSceneType::Exit){
      m_bGameLoop = false;
    }
  }
}

void Game::InputHandler()
{
  m_ScenesController.InputHandler();
}

void Game::Update(float dt)
{
  m_ScenesController.Update(dt);
}

void Game::Render()
{
  m_ScenesController.Render();
}

Uint32 Game::GetDeltaTime(Uint32 previous,float offset)
{
 return ((SDL_GetTicks() - previous) + offset); 
}