#ifndef SnakeGame_SPRITE_ANIMATION_HPP
#define SnakeGame_SPRITE_ANIMATION_HPP
#include "SDL2/SDL.h"
#include "../Texture/Texture.hpp"

class TextureAnimation{
public:
    TextureAnimation();
    ~TextureAnimation();

    Base::Ref<SDL_Texture> LoadSpriteSheet(const std::string& path, const Vec2& max_frame){
       m_MaxFrame = max_frame;
       return m_SpriteSheet.LoadTexture(path);
    }

    void SetPosition(const Vec2& pos){
        m_SpriteSheet.SetTexturePosition(pos);
    }

    void SetTextureSize(const TextureSize& size){
        m_SpriteSheet.SetTextureSize(size);
    }

    TextureSize GetTextureSize(){
        return m_SpriteSheet.GetTextureSize();
    }

    void SetMaxFrame(const Vec2& max_frame){
        m_MaxFrame = max_frame;
    }

    void SetFrameSize(const TextureSize& frame_size){
        m_FrameSize = frame_size;
        m_SpriteSheet.SetTextureSize<SourceRect>(m_FrameSize);
    }
    
    void ShareSpriteSheet(const Texture& texture, const Vec2& max_frame){
        m_SpriteSheet.ShareSDLTexture(texture);
        m_MaxFrame = max_frame;
    }

    void Pause(){m_IsPaused = true;}
    void UnPause(){m_IsPaused = false;}
    
    bool IsFinished() const {return m_IsFinished;}

    void MoveFrameForward();

    void Render();

    void Refresh();
    
private:
    Vec2 m_Pos; // x - represent current_frame, y - represents row
    Vec2 m_MaxFrame;

    Texture m_SpriteSheet;
    TextureSize m_FrameSize;
    bool m_IsFinished = false;
    bool m_IsPaused = false;
};

// class SpriteAnimation{
//     public:
//     SpriteAnimation();
//     ~SpriteAnimation();
//     void Update();

//     int GetCurrentFrame() const { return m_CurrentFrame; }
//     int GetCurrentFrame() { return m_CurrentFrame; }
//     int GetFrameToRender() { return (m_CurrentFrame * m_stride); }
// /**
//  * @brief Specifies the frame offset between consecutive generic frames
// */
//     void set_Stride(int stride){ m_stride = stride; }
//     void set_MaxFrames(int max_frames){ this->m_MaxFrames = max_frames;}
// /**
//  * @brief If false animation will be played once, otherwise until 'destroy'
// */
//     void set_LoopedAnim(bool status) { this->m_LoopedAnim = status;}
    
//     private:
//     int m_MaxFrames;
//     int m_CurrentFrame;
//     bool m_LoopedAnim;
//     int m_stride;
// };

#endif // SnakeGame_SPRITE_ANIMATION_HPP