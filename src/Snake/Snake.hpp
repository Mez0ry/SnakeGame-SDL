#ifndef SnakeGame_SNAKE_HPP
#define SnakeGame_SNAKE_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Map.hpp"
#include "SDL2/SDL.h"

/** SnakeBody*/
#include "SnakeBody.hpp"
#include "../GameScenes/GameScene.hpp"

class Snake : public Entity {
public:
  Snake();
  ~Snake();

  void OnCreate();
  void OnDestroy();

  void InputHandler();
  void Update(float dt);

  void OnRender() override;

  bool isPlayer() const override { return true; }
 
  void set_MoveDir(const Vec2& dir_vec) {
    m_DirectionVec = dir_vec;
  }

  void GrowBody(){
    m_SnakeBody.AddLength();
  }

   void SetPosition(const Vec2 &pos) override{
    m_SnakePosition = pos;
  }

  const Vec2& GetPosition() const override{
    return m_SnakePosition;
  }

  void SetSize(const TextureSize &size){
    for(int i = 0;i<4;i++){
      m_SnakeTextures[i].SetTextureSize(size);
    }
    m_Texture.SetTextureSize(size);
    m_SnakeBody.GetTexture().SetTextureSize(size);
  }
  
  const TextureSize GetSize() const{
    return m_Texture.GetTextureSize();
  }
  
  Texture& GetTexture(){
    return m_Texture;
  }
  
private:
  Texture m_Texture; // Texture that will be rendered
  SnakeBody m_SnakeBody;
  Vec2 m_SnakePosition;
  Vec2 m_PrevSnakePosition;

  Vec2 m_DirectionVec;
  int m_ScalarVelocity;

  Texture m_SnakeTextures[4]; //Preloaded textures
};
#endif //! SnakeGame_SNAKE_HPP