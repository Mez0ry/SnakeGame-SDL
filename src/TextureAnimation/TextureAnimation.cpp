#include "TextureAnimation.hpp"

TextureAnimation::TextureAnimation() : m_Pos(0,0),m_IsFinished(false), m_IsPaused(false)
{
    
}

TextureAnimation::~TextureAnimation()
{
    
}

void TextureAnimation::MoveFrameForward(){
    if(m_IsPaused) return;

    if(m_Pos.x + 1 > m_MaxFrame.x){
        if(m_MaxFrame.x + 1 > m_MaxFrame.x && m_Pos.y + 1 > m_MaxFrame.y){
          m_IsFinished = true;
        }else{
          m_Pos.y++;
          m_Pos.x = 0;
        }
    }else{
        m_Pos.x += 1;
    }
    
    m_SpriteSheet.SetTexturePosition<SourceRect>({m_Pos.x * m_FrameSize.GetWidth() , m_Pos.y * m_FrameSize.GetHeight()});
}

void TextureAnimation::Refresh(){

    m_Pos.x = 0;
    m_Pos.y = 0;
    m_IsFinished = false;
    m_SpriteSheet.SetTexturePosition<SourceRect>({m_Pos.x * m_FrameSize.GetWidth(),m_Pos.y * m_FrameSize.GetHeight()});
}

void TextureAnimation::Render(){
    if(m_IsFinished || m_IsPaused) return;

    m_SpriteSheet.RenderTexture();
}