#ifndef SnakeGame_GameScenes_CMENU_HPP
#define SnakeGame_GameScenes_CMENU_HPP
#include "GameScene.hpp"
#include <bitset>
#include "../FontManager/FontManager.hpp"

class CMenu : public GameScene
{
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
    const char *m_labels[3] = {"Play", "Stats", "Exit"};
    FontManager m_MenuText[3];
    SDL_Color m_color[2] = {{255, 255, 255, 255}, {255, 0, 0, 255}};
};
#endif //! SnakeGame_GameScenes_CMENU_HPP