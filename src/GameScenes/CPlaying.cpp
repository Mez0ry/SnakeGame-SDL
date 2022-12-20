#include "CPlaying.hpp"

CPlaying::CPlaying() {
  m_pFoodFlyweight = std::make_shared<FoodFlyweight>();

  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string food_texture_path;

  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "apple.png";
  m_pFoodFlyweight->AddFood(FoodName::APPLE,FoodType::Edible,6,food_texture_path);
  
  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "water_melon.png";
  m_pFoodFlyweight->AddFood(FoodName::WATER_MELON,FoodType::Edible,6,food_texture_path);
  
  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "star_fruit.png";
  m_pFoodFlyweight->AddFood(FoodName::STAR_FRUIT,FoodType::Edible,10,food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "burger.png";
  m_pFoodFlyweight->AddFood(FoodName::BURGER,FoodType::InEdible,8,food_texture_path);
  
  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "hotdog.png";
  m_pFoodFlyweight->AddFood(FoodName::HOTDOG,FoodType::InEdible,3,food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder()  + symbol + "assets" + symbol + "food" + symbol + "steak.png";
  m_pFoodFlyweight->AddFood(FoodName::STEAK,FoodType::InEdible,2,food_texture_path);
  
  m_Snake.set_MapState(m_Map.get_MapState());

  for (short int i = 0; i < FOOD_SIZE; i++) {
    m_food[i].set_MapState(m_Map.get_MapState());

    m_food[i].set_FoodFlyweight(m_pFoodFlyweight);
  }

  m_CollideSystem.AddObserver(&m_GameScore);
  m_GameScore.AddObserver(&m_AchievementSystem);
}

CPlaying::~CPlaying() {}

void CPlaying::OnCreate() {
  m_GameScore.OnCreate();
  m_Map.OnCreate();
  m_Snake.OnCreate();
  
  for (short int i = 0; i < FOOD_SIZE; i++) {
    m_food[i].RespawnNewFood();
  }

}

void CPlaying::BeforeDestruction()
{
   this->Render();
   TakeAndSaveScreenShot();
}

void CPlaying::OnDestroy() {
  m_Snake.OnDestroy();
  m_GameScore.OnDestroy();
}

void CPlaying::InputHandler() {
  if (SDL_PollEvent(&m_event)) {
    switch (m_event.type) {
    case SDL_QUIT: {
      g_GameSceneType = GameSceneType::Exit;
      break;
    }
    case SDL_KEYDOWN: {
      switch (m_event.key.keysym.sym) {
      case SDLK_LEFT:
        m_Snake.get_SnakeState().moving.move_dir = MoveDir::LEFT;
        m_Snake.get_SnakeState().type = SNAKE_MOVING_STATE;
        break;
      case SDLK_RIGHT:
        m_Snake.get_SnakeState().moving.move_dir = MoveDir::RIGHT;
        m_Snake.get_SnakeState().type = SNAKE_MOVING_STATE;
        break;
      case SDLK_UP:
        m_Snake.get_SnakeState().moving.move_dir = MoveDir::UP;
        m_Snake.get_SnakeState().type = SNAKE_MOVING_STATE;
        break;
      case SDLK_DOWN:
        m_Snake.get_SnakeState().moving.move_dir = MoveDir::DOWN;
        m_Snake.get_SnakeState().type = SNAKE_MOVING_STATE;
        break;
      case SDLK_r: {

        break;
      }
      case SDLK_ESCAPE: {
        g_GameSceneType = GameSceneType::Pause;
        break;
      }
      } // !switch m_event.key.keysym.sym
      break;
    }
    } // !switch
  }
  m_Snake.InputHandler();
}

void CPlaying::Update() {
  m_Snake.Update();
  for (short int i = 0; i < FOOD_SIZE; i++) {
    m_food[i].Update();

    if(m_CollideSystem.IsColliding(m_Snake, m_food[i])){
      m_Snake.get_SnakeState().type = SNAKE_GROW_STATE;
    }
  }
  
  m_GameScore.Update();
  m_AchievementSystem.Update();
}

void CPlaying::Render() {
  for (short int i = 0; i < FOOD_SIZE; i++) {
    m_food[i].Render();
  }
  m_Map.Render();
  m_Snake.Render();
  m_GameScore.Render();
  m_AchievementSystem.Render();
}


void CPlaying::TakeAndSaveScreenShot()
{
  const std::string& symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path;
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CPause" + symbol;
  std::string filename = "background.bmp";
  SDL_Surface *sshot = SDL_CreateRGBSurface(0, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight(), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_RenderReadPixels(CSDLContext::instance().get_renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

  SDL_SaveBMP(sshot, (texture_path + filename).c_str());
  SDL_FreeSurface(sshot);
}