#ifndef SnakeGame_GameScenes_CPLAYING_HPP
#define SnakeGame_GameScenes_CPLAYING_HPP
#include "../Map.hpp"
#include "GameScene.hpp"
#include "../Snake/Snake.hpp"
#include "../Food/Food.hpp"
#include "../GameScore/GameScore.hpp"
#include "../CollideSystem/CollideSystem.hpp"
#include "../AchievementSystem/AchievementSystem.hpp"
#include "../Timer/Timer.hpp"
#include <list>

class CPlaying : public GameScene
{
public:
  CPlaying();
  ~CPlaying();

  void OnCreate() override;
  void BeforeDestruction() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update() override;
  void Render() override;
  GameSceneType get_SceneTypeToIgnore() override { return  GameSceneType::Pause;}
private:
  void TakeAndSaveScreenShot();

private:
  Map m_Map;
  Snake m_Snake;
  Food m_food[FOOD_SIZE];
  std::shared_ptr<FoodFlyweight> m_pFoodFlyweight;
  GameScore m_GameScore;
  CollideSystem m_CollideSystem;
  AchievementSystem m_AchievementSystem;
  Timer m_StartToFinishTimer;

  std::list<double> m_InGameTimeStack;
};
#endif //! SnakeGame_GameScenes_CPLAYING_HPP