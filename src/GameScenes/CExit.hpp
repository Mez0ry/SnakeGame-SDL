#ifndef SnakeGame_GameScenes_CEXIT_HPP
#define SnakeGame_GameScenes_CEXIT_HPP
#include "GameScene.hpp"
class CExit : public GameScene {
public:
  CExit();
  ~CExit();

  void OnCreate() override;
  void BeforeDestruction() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update() override;
  void Render() override;

private:
};
#endif //! SnakeGame_GameScenes_CEXIT_HPP