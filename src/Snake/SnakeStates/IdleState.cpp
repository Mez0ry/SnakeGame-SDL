#include "IdleState.hpp"

IdleState::IdleState()
{
  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_left.png";
  m_Texture.LoadTexture(texture_path);

  m_Texture.set_srcRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
}

IdleState::~IdleState()
{
  m_Texture.DestroyTexture();
}

void IdleState::InputHandler(const Snake_State &state)
{
  m_SnakeState = state;
}

void IdleState::Update(EntityPosition &position_to_update, SquareType **map_state)
{
  this->m_SnakePosition = position_to_update;
  this->m_MapState = map_state;

  m_Texture.set_dstRect(MapUtils::CorrectWidthPosOnTheMap(m_SnakePosition.x), MapUtils::CorrectHeightPosOnTheMap(m_SnakePosition.y), TextureConstants::TextureWidth, TextureConstants::TextureHeight);

  if (EntIsOutOfMap())
  {
    g_GameSceneType = GameSceneType::Menu;
    return;
  }

  m_MapState[m_SnakePosition.y][m_SnakePosition.x] = SquareType::ENTITY;
}

void IdleState::Render()
{

  m_Texture.RenderTexture();
}
