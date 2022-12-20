#include "MovingState.hpp"

MovingState::MovingState()
{
  m_TextureDrawIndex = 0;
  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_left.png";
  m_Texture[0].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_right.png";
  m_Texture[1].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_up.png";
  m_Texture[2].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_down.png";
  m_Texture[3].LoadTexture(texture_path);

  for (int i = 0; i < static_cast<int>(internal_sizes::MAX_TEXTURE); i++)
  {
    m_Texture[i].set_dstRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
    m_Texture[i].set_srcRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
  }
}

MovingState::~MovingState()
{
  for (int i = 0; i < static_cast<int>(internal_sizes::MAX_TEXTURE); i++)
  {
    m_Texture[i].DestroyTexture();
  }
}

void MovingState::InputHandler(const Snake_State &state)
{
  m_SnakeState = state;
}

void MovingState::Update(EntityPosition &position_to_update, SquareType **map_state)
{
  this->m_MapState = map_state;
  m_SnakePrevPosition = position_to_update;
  switch (m_SnakeState.moving.move_dir)
  {
  case MoveDir::LEFT:
  {
    m_TextureDrawIndex = 0;
    position_to_update.x -= 1;
    break;
  }
  case MoveDir::RIGHT:
  {
    m_TextureDrawIndex = 1;
    position_to_update.x += 1;
    break;
  }
  case MoveDir::UP:
  {
    m_TextureDrawIndex = 2;
    position_to_update.y -= 1;
    break;
  }
  case MoveDir::DOWN:
  {
    m_TextureDrawIndex = 3;
    position_to_update.y += 1;
    break;
  }
  } //! switch
 
  this->m_SnakePosition = position_to_update;
 
  m_Texture[m_TextureDrawIndex].set_dstRect(MapUtils::CorrectWidthPosOnTheMap(m_SnakePosition.x), MapUtils::CorrectHeightPosOnTheMap(m_SnakePosition.y), TextureConstants::TextureWidth, TextureConstants::TextureHeight);

  if (EntIsOutOfMap())
  {
    g_GameSceneType = GameSceneType::Menu;
    return;
  }

  m_MapState[m_SnakePrevPosition.y][m_SnakePrevPosition.x] = SquareType::BACKGROUND;

  m_MapState[m_SnakePosition.y][m_SnakePosition.x] = SquareType::ENTITY;
}

void MovingState::Render()
{
  m_Texture[m_TextureDrawIndex].RenderTexture();
}
