#include "Food.hpp"
Food::Food() : m_TextureSize(32,32) {
 
}

Food::~Food() {

}

void Food::Update(float dt) {
  
  // switch(m_pFoodModel->StrategyType->execute(m_TimeStamp.GetDurationInSeconds())){
  //   case FoodEvent::RESPAWN_FOOD:{
  //     RespawnNewFood();
  //     break;
  //   }
  // }
  
}

void Food::OnRender() {
  
}

void Food::RespawnNewFood() {
  this->RandomizePosition();
  this->randomizeFoodTexture();
}

void Food::RandomizePosition() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> PositionX(0, CAppSettings::instance().get_MapWidth() - 1);

  std::uniform_int_distribution<std::mt19937::result_type> PositionY(0, CAppSettings::instance().get_MapHeight() - 1);

  m_Position.x = PositionX(rng);
  m_Position.y = PositionY(rng);
}

inline void Food::randomizeFoodTexture() {
  auto path = CAppSettings::instance().get_SourceFolder() + CAppSettings::instance().GetCorrectedPath("/assets/food/configs/food.cfg");
  
  Serializer des;
  if(Serializer::Deserialize(des,path)){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand_food(0, des.GetObjectsSize() - 1);
    auto& entity_context = des[rand_food(rng)];
    m_Points = entity_context["points"].GetAs<int>(0);
    m_Texture.LoadTexture(CAppSettings::instance().get_SourceFolder() + entity_context["texture_path"].GetAs<std::string>(0));
    
    m_Texture.SetRect<SourceRect>({0,0},TextureSize(40,40));
    m_Texture.SetRect({0,0},m_TextureSize);
  }
  m_TimeStamp.Start();
}