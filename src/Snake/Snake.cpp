#include "Snake.hpp"
Snake::Snake() : m_MapState(nullptr)
{
  m_SnakeStatesController.AddState(std::make_shared<MovingState>(), SNAKE_MOVING_STATE);
  m_SnakeStatesController.AddState(std::make_shared<IdleState>(), SNAKE_IDLE_STATE);

  m_SnakeStatesController.TransitionTo(SNAKE_IDLE_STATE);
  
  const std::string & symbolref = CAppSettings::instance().get_SlashSymbol();
  std::string poison_texture_path = CAppSettings::instance().get_SourceFolder() + symbolref + "assets" + symbolref + "snake" + symbolref + "Ultimate" + symbolref + "poison_particle_vfx.png";
 
  m_PoisonTexture.LoadTexture(poison_texture_path);
  m_PoisonTexture.set_dstRect(0,0,32,32);
  m_PoisonTexture.set_srcRect(0,0,32,32);
  
  m_PoisonAnimation.set_Stride(32);
  m_PoisonAnimation.set_MaxFrames(15);
}

Snake::~Snake() {
  
}

void Snake::OnCreate()
{
  m_SnakePosition.x = CAppSettings::instance().get_MapWidth() / 2;
  m_SnakePosition.y = CAppSettings::instance().get_MapHeight() / 2;

  m_SnakeBody.Reset();
  m_SnakeStatesController.TransitionTo(SNAKE_IDLE_STATE);
  m_SnakeState.type = SNAKE_IDLE_STATE;
}

void Snake::OnDestroy()
{
  
}

void Snake::InputHandler()
{
  	switch(m_SnakeState.type){
		case SNAKE_MOVING_STATE:{
			m_SnakeStatesController.TransitionTo(SNAKE_MOVING_STATE);
			break;
		}
		case SNAKE_IDLE_STATE:{
			m_SnakeStatesController.TransitionTo(SNAKE_IDLE_STATE);
			break;
		}
    case SNAKE_GROW_STATE:{
      m_SnakeBody.AddLength();
      m_SnakeState.type = SNAKE_MOVING_STATE;
      break;
    }
	}
  m_SnakeStatesController.InputHandler(m_SnakeState);
  
}

void Snake::Update()
{
  m_SnakeStatesController.update(m_SnakePosition, m_MapState);
  if (m_SnakeState.type != SNAKE_IDLE_STATE)
    m_SnakeBody.Update(m_MapState, m_SnakePosition);
    m_PoisonAnimation.Update();
}

void Snake::Render()
{
  m_SnakeStatesController.render();
  if (m_SnakeState.type != SNAKE_IDLE_STATE)
    m_SnakeBody.Render();
  m_PoisonTexture.set_srcRect(m_PoisonAnimation.GetFrameToRender(),0,32,32);
  m_PoisonTexture.RenderTexture();
  m_PoisonTexture.ReloadTexture();
}
