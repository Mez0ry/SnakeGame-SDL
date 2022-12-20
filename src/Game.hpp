#ifndef SnakeGame_GAME_HPP
#define SnakeGame_GAME_HPP
#include "CSDLContext/CSDLContext.hpp"
#include "GameScenes/GameScenesController.hpp"
#include "SoundManager/SoundManager.hpp"
class Game
{
private:
    uint32_t m_fps = 60;
	uint32_t m_frameDelay = 3000 / m_fps;
	uint32_t m_frameStart;
	uint32_t m_frameTime;
    bool m_bGameLoop = false;
public:
    Game();
    ~Game();
    void Play();

    void InputHandler();
    void Update();
    void Render();

private:
    SDL_Event m_event;
    GameScenesController m_ScenesController;
};
#endif //! SnakeGame_GAME_HPP