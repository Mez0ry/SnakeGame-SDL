#include "Food.hpp"
Food::Food() {
 
}

Food::~Food() {

}

void Food::LoadTexture(const char *path) {
  std::string texture_path = path;
  m_pFoodModel->Texture.LoadTexture(texture_path);
}

void Food::set_DstRect(int x, int y, int w, int h) {
  m_pFoodModel->Texture.set_dstRect(x, y, w, h);
}

void Food::set_SrcRect(int x, int y, int w, int h) {
  m_pFoodModel->Texture.set_srcRect(x, y, w, h);
}

void Food::Update() {
  if(m_pFoodModel->Type == FoodType::InEdible){
    std::chrono::seconds time(RESPAWN_INEDIBLE_FOOD_IN);
    if(m_Timer.GetDurationInSeconds() >= time.count()){
    RespawnNewFood();
    }
  }
}

void Food::Render() {
  if (m_Position.x < 0 || m_Position.y < 0 || m_Position.x >= CAppSettings::instance().get_MapWidth() || m_Position.y >= CAppSettings::instance().get_MapHeight())
    return;

  m_MapState[m_Position.y][m_Position.x] = SquareType::ENTITY;
  
  m_pFoodModel->Texture.set_dstRect(MapUtils::CorrectWidthPosOnTheMap(m_Position.x),MapUtils::CorrectHeightPosOnTheMap(m_Position.y), TextureConstants::TextureWidth, TextureConstants::TextureHeight);

  m_pFoodModel->Texture.RenderTexture();
}

void Food::set_MapState(SquareType **map_state) {
  this->m_MapState = map_state;
}

void Food::set_FoodFlyweight(const std::shared_ptr<FoodFlyweight>& pFoodFlyweight){
  this->m_pFoodFlyweight = pFoodFlyweight;
}

void Food::RespawnNewFood() {
  this->randomizePositionOnMap();
  this->randomizeFoodTexture();
}

void Food::randomizePositionOnMap() {
  if (m_Position.x > 0 && m_Position.y > 0 &&
      m_Position.x < CAppSettings::instance().get_MapWidth() &&
      m_Position.y < CAppSettings::instance().get_MapHeight()) {
    m_MapState[m_Position.y][m_Position.x] = SquareType::BACKGROUND;
  }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> PositionX(0, CAppSettings::instance().get_MapWidth() - 1);

  std::uniform_int_distribution<std::mt19937::result_type> PositionY(0, CAppSettings::instance().get_MapHeight() - 1);

  m_Position.x = PositionX(rng);
  m_Position.y = PositionY(rng);
}

inline void Food::randomizeFoodTexture() {

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> food_type(0, 5);

  std::string symbol = CAppSettings::instance().get_SlashSymbol();
  std::string food_texture_path;

  m_pFoodModel = m_pFoodFlyweight->get_FoodModel(static_cast<FoodName>(food_type(rng)));
  m_Timer.Start();
}

bool Food::isColliding(const EntityPosition &pos) {
  return (m_Position.x == pos.x && m_Position.y == pos.y) ? true : false;
}
