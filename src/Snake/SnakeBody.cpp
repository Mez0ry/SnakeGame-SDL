#include "SnakeBody.hpp"

SnakeBody::SnakeBody() : m_CurrSize(1)
{
    const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "body.png";
    m_SnakeBodyTexture.LoadTexture(texture_path);
    m_SnakeBodyTexture.set_Rect<SourceRect>(0, 0, 32, 32);
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

    m_BodyPosition.x = snake_position.x * m_SnakeBodyTexture.get_Rect<SourceRect>().w;
    m_BodyPosition.y = snake_position.y * m_SnakeBodyTexture.get_Rect<SourceRect>().h;
    m_BodyPosition.w = m_BodyPosition.h = 32;
    rq.push_front(m_BodyPosition);

    while (rq.size() > m_CurrSize)
    {
        map_state[rq.back().y / m_SnakeBodyTexture.get_Rect<SourceRect>().h][rq.back().x / m_SnakeBodyTexture.get_Rect<SourceRect>().w] = SquareType::BACKGROUND;
        rq.pop_back();
    }

}

void SnakeBody::Render()
{
    for(int i = 0;i < rq.size(); i++){
        if(i == 0) continue;
        
        if (rq[i].y / m_SnakeBodyTexture.get_Rect<SourceRect>().h > CAppSettings::instance().get_MapHeight() || rq[i].x / m_SnakeBodyTexture.get_Rect<SourceRect>().w> CAppSettings::instance().get_MapWidth() || rq[i].y / m_SnakeBodyTexture.get_Rect<SourceRect>().h < 0 || rq[i].x / m_SnakeBodyTexture.get_Rect<SourceRect>().w < 0)
        {
            return;
        }
        m_MapState[rq[i].y / m_SnakeBodyTexture.get_Rect<SourceRect>().h][rq[i].x / m_SnakeBodyTexture.get_Rect<SourceRect>().w] = SquareType::ENTITY;
        
        m_SnakeBodyTexture.set_Rect((rq[i].x / m_SnakeBodyTexture.get_Rect<SourceRect>().w) * m_SnakeBodyTexture.get_Rect<SourceRect>().w + CAppSettings::instance().get_WindowWidth() / CAppSettings::instance().get_MapWidth() ,(rq[i].y / m_SnakeBodyTexture.get_Rect<SourceRect>().h) * m_SnakeBodyTexture.get_Rect<SourceRect>().h + CAppSettings::instance().get_WindowWidth() / CAppSettings::instance().get_MapWidth(),32,32);
        m_SnakeBodyTexture.RenderTexture();
    }
}

void SnakeBody::Reset()
{
    m_CurrSize = 1;
    rq.clear();
}