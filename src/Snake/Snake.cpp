#include "Snake.hpp"

Snake::Snake() : m_DirectionVec(0,0) , m_ScalarVelocity(1)
{
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/snake/head_left.png");

  m_SnakeTextures[0].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/snake/head_right.png");
  m_SnakeTextures[1].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/snake/head_up.png");
  m_SnakeTextures[2].LoadTexture(texture_path);
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/snake/head_down.png");
  m_SnakeTextures[3].LoadTexture(texture_path);

  const int snake_texture_size = 4;
  
  for (int i = 0; i < snake_texture_size; i++)
  {
    m_SnakeTextures[i].SetTexturePosition({0,0});
    m_SnakeTextures[i].SetTexturePosition<SourceRect>({0,0});

    m_SnakeTextures[i].SetTextureSize({32,32});
    m_SnakeTextures[i].SetTextureSize<SourceRect>(TextureSize(40, 40));
  }
  m_Texture.SetTexturePosition({0,0});
  m_Texture.SetTexturePosition<SourceRect>({0,0});
  
  m_Texture.SetTextureSize({32,32});
  m_Texture.SetTextureSize<SourceRect>(TextureSize(40, 40));

}

Snake::~Snake() {
  
}

void Snake::OnCreate()
{
  m_SnakePosition.x = CAppSettings::instance().get_MapWidth() / 2;
  m_SnakePosition.y = CAppSettings::instance().get_MapHeight() / 2;

  m_SnakeBody.Reset();
  m_DirectionVec = {0,0};
}

void Snake::OnDestroy()
{
  
}

void Snake::InputHandler()
{
    m_PrevSnakePosition = m_SnakePosition;

    if(m_DirectionVec.x == -1 && m_DirectionVec.y == 0 || m_DirectionVec.x == 0 && m_DirectionVec.y == 0){
      m_Texture.ShareSDLTexture(m_SnakeTextures[0]);
    }else if (m_DirectionVec.x == 1 && m_DirectionVec.y == 0){
      m_Texture.ShareSDLTexture(m_SnakeTextures[1]);
    }else if(m_DirectionVec.x == 0 && m_DirectionVec.y == -1){
      m_Texture.ShareSDLTexture(m_SnakeTextures[2]);
    }else if(m_DirectionVec.x == 0 && m_DirectionVec.y == 1){
      m_Texture.ShareSDLTexture(m_SnakeTextures[3]);
    }
    
}

void Snake::Update(float dt)
{
  m_SnakePosition += ((m_DirectionVec * m_ScalarVelocity ) * dt); // TODO: Add (dt * ARBITARY TUNING)

  if (!Map::IsOnBoard(m_SnakePosition)) {
    g_GameSceneType = GameSceneType::Menu;
    return;
  }

  m_SnakeBody.Update(m_SnakePosition);
}

void Snake::OnRender()
{
  m_SnakeBody.Render();
}
