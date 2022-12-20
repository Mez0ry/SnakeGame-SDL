#include "SpriteAnimation.hpp"

SpriteAnimation::SpriteAnimation() : m_MaxFrames(-1), m_LoopedAnim(true),m_CurrentFrame(-1)
{
    
}

SpriteAnimation::~SpriteAnimation()
{
    
}

void SpriteAnimation::Update()
{
    if(m_CurrentFrame >= m_MaxFrames){
        m_CurrentFrame = -1;
    }

    m_CurrentFrame++;
}
