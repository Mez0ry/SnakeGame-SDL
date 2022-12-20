#include "GameScenesController.hpp"

GameScenesController::GameScenesController() : m_pCurrentScene(nullptr), m_CurrentSceneType(static_cast<GameSceneType>(-1))
{
  m_size = 0;
}

GameScenesController::~GameScenesController()
{
}

void GameScenesController::CollectScenes()
{
  std::shared_ptr<CPlaying> playing_scene = std::make_shared<CPlaying>();
  AddScene(playing_scene);
  std::shared_ptr<CMenu> menu_scene = std::make_shared<CMenu>();
  AddScene(menu_scene);
  std::shared_ptr<CPause> pause_scene = std::make_shared<CPause>();
  AddScene(pause_scene);
  std::shared_ptr<CStats> stats_scene = std::make_shared<CStats>();
  AddScene(stats_scene);
  std::shared_ptr<CExit> exit_scene = std::make_shared<CExit>();
  AddScene(exit_scene);
}

void GameScenesController::InputHandler()
{
  switch (g_GameSceneType)
  {
  case GameSceneType::Menu:
  {
    TransitionTo(GameSceneType::Menu);
    break;
  }
  case GameSceneType::Playing:
  {
    TransitionTo(GameSceneType::Playing);
    break;
  }
  case GameSceneType::Pause:
  {
    TransitionTo(GameSceneType::Pause);
    break;
  }
  case GameSceneType::Stats:
  {
    TransitionTo(GameSceneType::Stats);
    break;
  }
  } //! switch

  if (m_pCurrentScene != nullptr)
  {
    m_pCurrentScene->InputHandler();
  }
}

void GameScenesController::Update()
{
  if (m_pCurrentScene != nullptr)
  {
    m_pCurrentScene->Update();
  }
}
void GameScenesController::Render()
{
  if (m_pCurrentScene != nullptr)
  {
    m_pCurrentScene->Render();
  }
}

unsigned int GameScenesController::AddScene(std::shared_ptr<GameScene> pScene)
{
  m_ScenesMap.emplace(std::make_pair(m_size++, std::move(pScene)));
  return m_size - 1;
}

void GameScenesController::TransitionTo(GameSceneType type)
{
  if (ScenesIsEqual(type))
    return;

  ScenesMapType::iterator it = m_ScenesMap.find(static_cast<int>(type));
  if (it == m_ScenesMap.end())
  {
    return;
  }

  m_PrevSceneType = g_GameSceneType;
  g_GameSceneType = type;
  m_CurrentSceneType = type;
  GameSceneType SceneTypeToIgnore = static_cast<GameSceneType>(-1);

  if (m_pCurrentScene != nullptr)
  {
    SceneTypeToIgnore = m_pCurrentScene->get_SceneTypeToIgnore();
    
    if (CurrentSceneEqualTo(SceneTypeToIgnore))
      m_pCurrentScene->BeforeDestruction();


    if (!CurrentSceneEqualTo(SceneTypeToIgnore))
    {
      m_pCurrentScene->OnDestroy();
      m_pCurrentScene = nullptr;
    }
  }

  m_pCurrentScene = it->second;

  if (!CurrentSceneEqualTo(SceneTypeToIgnore) || type == GameSceneType::Pause)
    m_pCurrentScene->OnCreate();
}

void GameScenesController::Remove(GameSceneType type)
{
  ScenesMapType::iterator it = m_ScenesMap.find(static_cast<int>(type));
  if (it != m_ScenesMap.end())
  {
    m_ScenesMap.erase(it);
    --m_size;
  }
}

constexpr bool GameScenesController::CurrentSceneEqualTo(GameSceneType rhs)
{
  return (m_CurrentSceneType == rhs);
}

bool GameScenesController::ScenesIsEqual(GameSceneType rhs)
{
  return (m_CurrentSceneType == rhs);
}