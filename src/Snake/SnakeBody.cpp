#include "SnakeBody.hpp"

SnakeBody::SnakeBody() : m_CurrSize(1)
{
    const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "body.png";
    m_SnakeBodyTexture.LoadTexture(texture_path);
    m_SnakeBodyTexture.set_srcRect(0, 0, 32, 32);
}

SnakeBody::~SnakeBody()
{
    m_SnakeBodyTexture.DestroyTexture();
}

void SnakeBody::AddLength()
{
    if (m_CurrSize < m_maxlength)
        m_CurrSize++;
}

void SnakeBody::Update(SquareType **map_state, EntityPosition &snake_position)
{
    this->m_MapState = map_state;

    m_BodyPosition.x = snake_position.x * TextureConstants::TextureWidth;
    m_BodyPosition.y = snake_position.y * TextureConstants::TextureHeight;
    m_BodyPosition.w = m_BodyPosition.h = 32;
    rq.push_front(m_BodyPosition);

    while (rq.size() > m_CurrSize)
    {
        map_state[rq.back().y / TextureConstants::TextureHeight][rq.back().x / TextureConstants::TextureWidth] = SquareType::BACKGROUND;
        rq.pop_back();
    }

}

void SnakeBody::Render()
{
    for(int i = 0;i < m_CurrSize; i++){
        if(i == 0) continue;
        
        if (rq[i].y / TextureConstants::TextureHeight > CAppSettings::instance().get_MapHeight() || rq[i].x / TextureConstants::TextureWidth > CAppSettings::instance().get_MapWidth() || rq[i].y / TextureConstants::TextureHeight < 0 || rq[i].x / TextureConstants::TextureWidth < 0)
        {
            return;
        }
        m_MapState[rq[i].y / TextureConstants::TextureHeight][rq[i].x / TextureConstants::TextureWidth] = SquareType::ENTITY;

        m_SnakeBodyTexture.set_dstRect(MapUtils::CorrectWidthPosOnTheMap(rq[i].x / TextureConstants::TextureWidth), MapUtils::CorrectHeightPosOnTheMap(rq[i].y / TextureConstants::TextureHeight));
        m_SnakeBodyTexture.RenderTexture();
    }
}

void SnakeBody::Reset()
{
    m_CurrSize = 1;
    rq.clear();
}