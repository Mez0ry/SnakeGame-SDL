#ifndef SnakeGame_GameScenes_CPAUSE_HPP
#define SnakeGame_GameScenes_CPAUSE_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../CSDLContext/CSDLContext.hpp"
#include "../Texture/Texture.hpp"
#include "../GUI/Text/Text.hpp"
#include "GameScene.hpp"

class CPause : public GameScene {
public:
  CPause();
  ~CPause();

  void OnCreate() override;
  void BeforeDestruction() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update() override;
  void Render() override;

  GameSceneType get_SceneTypeToIgnore() override {
    return GameSceneType::Playing;
  }

private:
  Texture m_BackgroundTexture;
  Text m_PauseText;
};
#endif //! SnakeGame_GameScenes_CPAUSE_HPP