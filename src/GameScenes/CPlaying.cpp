#include "CPlaying.hpp"

CPlaying::CPlaying()
{
  m_FoodVec.reserve(6);
  m_FoodVec.resize(6,Food());

  for(auto& food : m_FoodVec){
    food.RespawnNewFood();
    m_EntityList.push_back(std::ref(food));
  }

  m_CollideSystem.AddObserver(&m_GameScore);
  m_GameScore.AddObserver(&m_AchievementSystem);

  m_EntityList.push_back(std::ref(m_Snake));

  Resize();

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> random(0,4);

  std::string src_path = CAppSettings::instance().get_SourceFolder();

  const std::string explosions_path[5] = {
    {src_path + CAppSettings::instance().GetCorrectedPath("/assets/explosions/round_explosion/spritesheet/spritesheet.png")},
    {src_path + CAppSettings::instance().GetCorrectedPath("/assets/explosions/round_vortex/spritesheet/spritesheet.png")},
    {src_path + CAppSettings::instance().GetCorrectedPath("/assets/explosions/vertical_explosion/spritesheet/spritesheet.png")},
    {src_path + CAppSettings::instance().GetCorrectedPath("/assets/explosions/vertical_explosion_small/spritesheet/spritesheet.png")},
    {src_path + CAppSettings::instance().GetCorrectedPath("/assets/explosions/X_plosion/spritesheet/spritesheet.png")},
  };

  m_ExplosionPool.ForEach([&random,&rng,&explosions_path](TextureAnimation* animated_texture){
    animated_texture->LoadSpriteSheet(explosions_path[random(rng)],{9,8});
    animated_texture->SetFrameSize(TextureSize(100,100));
    animated_texture->SetTextureSize(TextureSize(32,32));
  });
  
}

CPlaying::~CPlaying() {}

void CPlaying::OnCreate()
{
  SDL_SetRenderDrawColor(CSDLContext::instance().get_renderer(),250,63,7,255);
  
  m_StartToFinishTimestamp.Start();

  m_GameScore.OnCreate();
  m_Map.OnCreate();
  m_Snake.OnCreate();

  for (auto& food : m_FoodVec)
  {
    food.RespawnNewFood();
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

  std::string file_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/CMatchHistory-Data.cfg");

  Serializer des;
  if(Serializer::Deserialize(des,file_path)){
    auto& node = des["CMatchHistory-Data"];
    auto& time_property = node["Time"];
    
    int write_index = 0;

    for(auto it = m_InGameTimeStack.begin(); it != m_InGameTimeStack.end();it++,write_index++){
      time_property.SetAs<double>(*it,write_index);
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
        m_Snake.set_MoveDir(Vec2(-1,0));
        break;
      case SDLK_RIGHT:
        m_Snake.set_MoveDir(Vec2(1,0));
        break;
      case SDLK_UP:
        m_Snake.set_MoveDir(Vec2(0,-1));
        break;
      case SDLK_DOWN:
        m_Snake.set_MoveDir(Vec2(0,1));
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

    case SDL_WINDOWEVENT:{
    switch(m_event.window.event){
        case SDL_WINDOWEVENT_RESIZED:{
          Resize();
          break;
        }
      }
      break;
    }//! SDL_WINDOW_EVENT

    } // !switch
  }
  m_Snake.InputHandler();
}

void CPlaying::Update(float dt)
{
  m_ExplosionsInUse.erase(std::remove_if(m_ExplosionsInUse.begin(),m_ExplosionsInUse.end(),[&](auto& info){
    if(info.resource->IsFinished()){
      info.resource->Refresh();
      m_ExplosionPool.ReturnResource(info);
      return true;
    }
    return false;
  }),m_ExplosionsInUse.end());

  for(auto& info : m_ExplosionsInUse){
    info.resource->MoveFrameForward();
  }
  
  m_Snake.Update(dt);
  for (auto& food : m_FoodVec)
  {
    food.Update(dt);
    auto prev_texture_pos = food.GetTexture().GetTexturePosition();
    if (m_CollideSystem.IsColliding(m_Snake, food))
    {
      auto& explosion = m_ExplosionPool.GetResource();

      explosion.resource->SetPosition(prev_texture_pos);

      m_ExplosionsInUse.push_back(explosion);
      m_Snake.GrowBody();
    }
  }

  m_GameScore.Update();
  m_AchievementSystem.Update();
}

void CPlaying::Render()
{
  m_Map.Render();


  for(auto& entity : m_EntityList){
    Map::RenderEntity(entity);
  }

  for(auto& explosion : m_ExplosionsInUse){
    explosion.resource->Render();
  }

  m_GameScore.Render();
  m_AchievementSystem.Render();
}

void CPlaying::TakeAndSaveScreenShot()
{
  std::string texture_path;
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CPause/background.bmp");
  int win_w{},win_h{};

  SDL_GetWindowSize(CSDLContext::instance().get_window(),&win_w,&win_h);

  SDL_Surface *sshot = SDL_CreateRGBSurface(0, win_w,win_h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_RenderReadPixels(CSDLContext::instance().get_renderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

  SDL_SaveBMP(sshot, (texture_path).c_str());
  SDL_FreeSurface(sshot);
}

void CPlaying::Resize()
{
  m_Map.OnResize();

  for(auto& entity : m_EntityList){
    entity.get().SetSize(m_Map.GetTextureSize());
  }

  m_ExplosionPool.ForEach([&](TextureAnimation* animated_texture){
    animated_texture->SetTextureSize(m_Map.GetTextureSize());
  });

  m_GameScore.OnResize();
}