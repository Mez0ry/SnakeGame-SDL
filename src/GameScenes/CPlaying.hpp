#ifndef SnakeGame_GameScenes_CPLAYING_HPP
#define SnakeGame_GameScenes_CPLAYING_HPP
#include "../Map.hpp"
#include "GameScene.hpp"
#include "../Snake/Snake.hpp"
#include "../Food/Food.hpp"
#include "../GameScore/GameScore.hpp"
#include "../CollideSystem/CollideSystem.hpp"
#include "../AchievementSystem/AchievementSystem.hpp"
#include "../Timestamp/Timestamp.hpp"
#include <list>
#include "../Serializer/Serializer.hpp"
#include "../ObjectPool.hpp"
#include "../TextureAnimation/TextureAnimation.hpp"

class CPlaying : public GameScene
{
public:
  CPlaying();
  ~CPlaying();

  void OnCreate() override;
  void BeforeDestruction() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update(float dt) override;
  void Render() override;
  GameSceneType get_SceneTypeToIgnore() override { return  GameSceneType::Pause;}
private:
  void TakeAndSaveScreenShot();
  void Resize();
  
private:
  std::vector<std::reference_wrapper<Entity>> m_EntityList;
  
  Map m_Map;
  Snake m_Snake;
  std::vector<Food> m_FoodVec;

  ObjectPool<TextureAnimation> m_ExplosionPool;
  std::vector<ResourceInfo<TextureAnimation*>> m_ExplosionsInUse;

  //std::shared_ptr<FoodFlyweight> m_pFoodFlyweight;
  GameScore m_GameScore;
  CollideSystem m_CollideSystem;
  AchievementSystem m_AchievementSystem;
  Utils::Timestamp m_StartToFinishTimestamp;
  
  std::list<double> m_InGameTimeStack;
};
#endif //! SnakeGame_GameScenes_CPLAYING_HPP