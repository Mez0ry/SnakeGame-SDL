#ifndef SnakeGame_GameScenes_CMENU_HPP
#define SnakeGame_GameScenes_CMENU_HPP
#include "../Sound/SoundManager.hpp"
#include "../GUI/Text/Text.hpp"
#include "../Vector.hpp"
#include "GameScene.hpp"
#include <array>

class CMenu : public GameScene {
public:
  CMenu();
  ~CMenu();

  void OnCreate() override;
  void OnDestroy() override;

  void InputHandler() override;
  void Update(float dt) override;
  void Render() override;
private:
  void Resize();
private:
  SoundManager m_SoundManager;
  const char *m_labels[3] = {"Play", "Stats", "Exit"};
  
  std::array<Text,3> m_MenuText;
  SDL_Color m_color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};
};
#endif //! SnakeGame_GameScenes_CMENU_HPP