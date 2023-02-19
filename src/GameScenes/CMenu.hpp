#ifndef SnakeGame_GameScenes_CMENU_HPP
#define SnakeGame_GameScenes_CMENU_HPP
#include "../Sound/SoundManager.hpp"
#include "../GUI/Text/Text.hpp"
#include "../Vector.hpp"
#include "GameScene.hpp"

class CMenu : public GameScene {
public:
  CMenu();
  ~CMenu();

  void OnCreate() override;
  void BeforeDestruction() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update() override;
  void Render() override;

private:
  SoundManager m_SoundManager;
  const char *m_labels[3] = {"Play", "Stats", "Exit"};
  Text m_MenuText[3];
  SDL_Color m_color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};
};
#endif //! SnakeGame_GameScenes_CMENU_HPP