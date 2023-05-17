#ifndef SnakeGame_FOOD_HPP
#define SnakeGame_FOOD_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Map.hpp"
#include <random>

/** Entity base class*/
#include "../Entity/Entity.hpp"

class Food : public Entity {
public:
  Food();
  ~Food();
  void Update(float dt) override;
  void OnRender() override;

  int GetPoints() const {return m_Points;}

  void RespawnNewFood();

  bool isPlayer() const override { return false; }
public:

  void SetPosition(const Vec2 &pos) override{
    m_Position = pos;
  }

  const Vec2& GetPosition() const override{
    return m_Position;
  }

  void SetSize(const TextureSize &size){
    m_TextureSize = size;
    this->m_Texture.SetTextureSize(m_TextureSize);
  }
  
  const TextureSize GetSize() const{
    return m_Texture.GetTextureSize();
  }
  
  Texture& GetTexture(){
    return m_Texture;
  }

private:
  void RandomizePosition();
  void randomizeFoodTexture();

  TextureSize m_TextureSize;
  Texture m_Texture;
  Vec2 m_Position;
  int m_Points;
  Utils::Timestamp m_TimeStamp;
};
#endif //! SnakeGame_FOOD_HPP