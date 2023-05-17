#include "SnakeBody.hpp"

SnakeBody::SnakeBody() : m_CurrSize(1)
{
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/snake/body.png");
    m_SnakeBodyTexture.LoadTexture(texture_path);
    m_SnakeBodyTexture.SetTexturePosition<SourceRect>({0,0});
    m_SnakeBodyTexture.SetTexturePosition({0,0});

    m_SnakeBodyTexture.SetTextureSize<SourceRect>(TextureSize(40, 40));
    m_SnakeBodyTexture.SetTextureSize(TextureSize(32, 32));
}

SnakeBody::~SnakeBody()
{

}

void SnakeBody::AddLength()
{
    if (m_CurrSize < m_maxlength)
        m_CurrSize++;
}

void SnakeBody::Update(Vec2 &snake_position)
{
    m_BodyDq.push_front(snake_position);

    while (m_BodyDq.size() > m_CurrSize)
    {
        m_BodyDq.pop_back();
    }

}

void SnakeBody::Render()
{
    for(int i = 0;i < m_BodyDq.size(); i++){
        if(i == 0) continue;
        
        if(Map::IsOnBoard(m_BodyDq[i])){
            Map::RenderTextureAt(m_SnakeBodyTexture,m_BodyDq[i]);
        }
    }
}

void SnakeBody::Reset()
{
    m_CurrSize = 1;
    m_BodyDq.clear();
}