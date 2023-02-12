#include "Snake.hpp"

Snake::Snake() : m_MapState(nullptr)
{
  m_Model.m_TextureDrawIndex = 0;

  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_left.png";

  m_Model.m_SnakeTextures[0].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_right.png";
  m_Model.m_SnakeTextures[1].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_up.png";
  m_Model.m_SnakeTextures[2].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "snake" + symbol + "head_down.png";
  m_Model.m_SnakeTextures[3].LoadTexture(texture_path);

  const int snake_texture_size = 4;
  for (int i = 0; i < snake_texture_size; i++)
  {
    m_Model.m_SnakeTextures[i].set_dstRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
    m_Model.m_SnakeTextures[i].set_srcRect(0, 0, TextureConstants::TextureWidth, TextureConstants::TextureHeight);
  }
  
}

Snake::~Snake() {
  
}

void Snake::OnCreate()
{
  m_Model.m_SnakePosition.x = CAppSettings::instance().get_MapWidth() / 2;
  m_Model.m_SnakePosition.y = CAppSettings::instance().get_MapHeight() / 2;
  m_Model.m_SnakeTextures[m_Model.m_TextureDrawIndex].set_dstRect(MapUtils::CorrectWidthPosOnTheMap(m_Model.m_SnakePosition.x),MapUtils::CorrectHeightPosOnTheMap(m_Model.m_SnakePosition.y), TextureConstants::TextureWidth, TextureConstants::TextureHeight);
  m_SnakeBody.Reset();
  m_MoveDir = MoveDir::UNKNOWN;
}

void Snake::OnDestroy()
{
  
}

void Snake::InputHandler()
{
  m_MoveToCommand.SetDir(m_MoveDir);
  m_MoveToCommand.Execute(m_Model);
}

void Snake::Update()
{
  m_SnakeBody.Update(m_MapState, m_Model.m_SnakePosition);
}

void Snake::Render()
{
  if(m_Model.m_TextureDrawIndex >= 0 && m_Model.m_TextureDrawIndex < 4){
    m_Model.m_SnakeTextures[m_Model.m_TextureDrawIndex].RenderTexture();
  }
  m_SnakeBody.Render();
}
