#ifndef SnakeGame_IGameScenes_HPP
#define SnakeGame_IGameScenes_HPP
#include "SDL2/SDL.h"

enum class GameSceneType { Playing, Menu, Pause, Stats, Exit};

/**
 * @brief holds current game scene type, used to change scenes
 */
inline GameSceneType g_GameSceneType;

class GameScene {
public:
  virtual ~GameScene() {}

  virtual void OnCreate() = 0;
  /**
   * @brief Used to do some operations before destruction
  */
  virtual void BeforeDestruction(){}
  virtual void OnDestroy() = 0;
  virtual void InputHandler() = 0;
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  /**
   * @brief Ignores the call to the OnDestroy method if the scene at the time of transition is not equal to the type of scene obtained from this method
  */
  virtual GameSceneType get_SceneTypeToIgnore() { return static_cast<GameSceneType>(-2);}
protected:
  SDL_Event m_event;
  SDL_Renderer *m_renderer;
};
#endif //! SnakeGame_IGameScenes_HPP