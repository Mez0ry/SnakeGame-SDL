#ifndef SnakeGame_SPRITE_ANIMATION_HPP
#define SnakeGame_SPRITE_ANIMATION_HPP
#include "SDL2/SDL.h"
class SpriteAnimation{
    public:
    SpriteAnimation();
    ~SpriteAnimation();
    void Update();

    int GetCurrentFrame() const { return m_CurrentFrame; }
    int GetCurrentFrame() { return m_CurrentFrame; }
    int GetFrameToRender() { return (m_CurrentFrame * m_stride); }
/**
 * @brief Specifies the frame offset between consecutive generic frames
*/
    void set_Stride(int stride){ m_stride = stride; }
    void set_MaxFrames(int max_frames){ this->m_MaxFrames = max_frames;}
/**
 * @brief If false animation will be played once, otherwise until 'destroy'
*/
    void set_LoopedAnim(bool status) { this->m_LoopedAnim = status;}
    
    private:
    int m_MaxFrames;
    int m_CurrentFrame;
    bool m_LoopedAnim;
    int m_stride;
};

#endif // SnakeGame_SPRITE_ANIMATION_HPP