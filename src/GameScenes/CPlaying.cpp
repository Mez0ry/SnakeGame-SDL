#include "CPlaying.hpp"

CPlaying::CPlaying()
{
  m_pFoodFlyweight = std::make_shared<FoodFlyweight>();

  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string food_texture_path;

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "apple.png";
  m_pFoodFlyweight->AddFood(FoodName::APPLE, FoodType::Edible, 6, food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "water_melon.png";
  m_pFoodFlyweight->AddFood(FoodName::WATER_MELON, FoodType::Edible, 6, food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "star_fruit.png";
  m_pFoodFlyweight->AddFood(FoodName::STAR_FRUIT, FoodType::Edible, 10, food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "burger.png";
  m_pFoodFlyweight->AddFood(FoodName::BURGER, FoodType::InEdible, 8, food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "hotdog.png";
  m_pFoodFlyweight->AddFood(FoodName::HOTDOG, FoodType::InEdible, 3, food_texture_path);

  food_texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "food" + symbol + "steak.png";
  m_pFoodFlyweight->AddFood(FoodName::STEAK, FoodType::InEdible, 2, food_texture_path);

  m_Snake.set_MapState(m_Map.get_MapState());

  for (short int i = 0; i < FOOD_SIZE; i++)
  {
    m_food[i].set_MapState(m_Map.get_MapState());

    m_food[i].set_FoodFlyweight(m_pFoodFlyweight);
  }

  m_CollideSystem.AddObserver(&m_GameScore);
  m_GameScore.AddObserver(&m_AchievementSystem);
}

CPlaying::~CPlaying() {}

void CPlaying::OnCreate()
{
  m_StartToFinishTimestamp.Start();

  m_GameScore.OnCreate();
  m_Map.OnCreate();
  m_Snake.OnCreate();

  for (short int i = 0; i < FOOD_SIZE; i++)
  {
    m_food[i].RespawnNewFood();
  }
}

void CPlaying::BeforeDestruction()
{
  this->Render();
  TakeAndSaveScreenShot();
}

void CPlaying::OnDestroy()
{
  m_Snake.OnDestroy();
  m_GameScore.OnDestroy();

  double time_in_game = m_StartToFinishTimestamp.GetDurationInSeconds();
  m_InGameTimeStack.push_front(time_in_game / 60);

  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string file_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "CMatchHistory-Data.cfg";

  Serializer des;
  if(Serializer::Deserialize(des,file_path)){
    auto& node = des["CMatchHistory-Data"];
    auto& time_property = node["Time"];
    
    int write_index = 0;

    for(auto it = m_InGameTimeStack.begin(); it != m_InGameTimeStack.end();it++,write_index++){
      time_property.set_Double(*it,write_index);
    }
  
    Serializer::Serialize(des,file_path);
  }
}

void CPlaying::InputHandler()
{
  while (SDL_PollEvent(&m_event))
  {
    switch (m_event.type)
    {
    case SDL_QUIT:
    {
      g_GameSceneType = GameSceneType::Exit;
      break;
    }
    case SDL_KEYDOWN:
    {
      switch (m_event.key.keysym.sym)
      {
      case SDLK_LEFT:
        m_Snake.set_MoveDir(MoveDir::LEFT);
        break;
      case SDLK_RIGHT:
         m_Snake.set_MoveDir(MoveDir::RIGHT);
        break;
      case SDLK_UP:
        m_Snake.set_MoveDir(MoveDir::UP);
        break;
      case SDLK_DOWN:
        m_Snake.set_MoveDir(MoveDir::DOWN);
        break;
      case SDLK_r:
      {

        break;
      }
      case SDLK_ESCAPE:
      {
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

void CPlaying::Update()
{
  m_Snake.Update();
  for (short int i = 0; i < FOOD_SIZE; i++)
  {
    m_food[i].Update();

    if (m_CollideSystem.IsColliding(m_Snake, m_food[i]))
    {
      m_Snake.GrowBody();
    }
  }

  m_GameScore.Update();
  m_AchievementSystem.Update();
}

void CPlaying::Render()
{
  for (short int i = 0; i < FOOD_SIZE; i++)
  {
    m_food[i].Render();
  }
  m_Map.Render();
  m_Snake.Render();
  m_GameScore.Render();
  m_AchievementSystem.Render();
}

void CPlaying::TakeAndSaveScreenShot()
{
  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string texture_path;
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CPause" + symbol;
  std::string filename = "background.bmp";
  SDL_Surface *sshot = SDL_CreateRGBSurface(0, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight(), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_RenderReadPixels(CSDLContext::instance().get_renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

  SDL_SaveBMP(sshot, (texture_path + filename).c_str());
  SDL_FreeSurface(sshot);
}