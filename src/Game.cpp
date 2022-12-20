#include "Game.hpp"

Game::Game() : m_bGameLoop(true)
{
  CSDLContext::instance().init();
  m_ScenesController.CollectScenes();
  m_ScenesController.TransitionTo(GameSceneType::Menu);
}

Game::~Game()
{
}

void Game::Play()
{

  while (m_bGameLoop)
  {
    SDL_RenderClear(CSDLContext::instance().get_renderer());
    m_frameStart = SDL_GetTicks();

    InputHandler();
    Update();
    Render();

    SDL_RenderPresent(CSDLContext::instance().get_renderer());
    m_frameTime = m_frameStart - m_frameStart;
    if (g_GameSceneType != GameSceneType::Menu)
    {
      if (m_frameDelay > m_frameTime)
      {
        SDL_Delay(m_frameDelay - m_frameTime);
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

void Game::Update()
{
  m_ScenesController.Update();
}

void Game::Render()
{
  m_ScenesController.Render();
}