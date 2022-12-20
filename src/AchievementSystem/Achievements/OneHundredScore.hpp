#ifndef SnakeGame_ACHIEVEMENTS_ONE_HUNDRED_SCORE_HPP
#define SnakeGame_ACHIEVEMENTS_ONE_HUNDRED_SCORE_HPP
#include "../Achievement.hpp"
#include <iostream>
#include <vector>
class OneHundredScore : public Achievement<OneHundredScore>{
    public:
    OneHundredScore();
    ~OneHundredScore();

    void Update();
    void Render();
    void set_IsUnlocking(bool status){m_isUnlocking = status;}
    bool get_IsUnlocking(){return m_isUnlocking;}
    bool IsUnlocked() { return m_isUnlocked; }
    void set_IsUnlocked(bool isUnlockedStatus){ this->m_isUnlocked = isUnlockedStatus;}
    private:
    bool m_isUnlocked = false;
    bool m_isUnlocking = false;
    TextureManager m_AchievementTexture;
    SDL_Rect m_Position;
    std::vector<bool> m_AnimationStages;
    int m_Seconds;
};
#endif //!SnakeGame_ACHIEVEMENTS_ONE_HUNDRED_SCORE_HPP