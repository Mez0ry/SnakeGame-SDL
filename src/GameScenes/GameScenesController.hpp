#ifndef SnakeGame_GameScenes_CONTROLLER_HPP
#define SnakeGame_GameScenes_CONTROLLER_HPP
#include <memory>
#include <unordered_map>

/**Scene headers */
#include "CExit.hpp"
#include "CMenu.hpp"
#include "CPause.hpp"
#include "CPlaying.hpp"
#include "CMatchHistory.hpp"

class GameScenesController {
private:
  using ScenesMapType =
      std::unordered_map<unsigned int, std::shared_ptr<GameScene>>;

public:
  GameScenesController();
  ~GameScenesController();
  /**
   * @brief Collects scenes and adding them to the map
  */
  void CollectScenes();
  void InputHandler();
  void Update();
  void Render();
  /**
   * @return id of added scene
  */
  unsigned int AddScene(std::shared_ptr<GameScene> pScene);
  void TransitionTo(GameSceneType type);
  void Remove(GameSceneType type);

private:
  constexpr bool CurrentSceneEqualTo(GameSceneType rhs);
  bool ScenesIsEqual(GameSceneType rhs);
  /**
   * @brief Used to do some operations before destruction
  */
  void BeforeDestruction(const std::shared_ptr<GameScene>& scene_ptr);

  ScenesMapType m_ScenesMap;
  std::shared_ptr<GameScene> m_pCurrentScene;
  unsigned int m_size = 0;
  GameSceneType m_CurrentSceneType;
  GameSceneType m_PrevSceneType;
};
#endif //! SnakeGame_GameScenes_CONTROLLER_HPP