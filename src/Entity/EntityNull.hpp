#ifndef SnakeGame_ENTITY_NULL_OBJECT_HPP
#define SnakeGame_ENTITY_NULL_OBJECT_HPP
#include "Entity.hpp"

class EntityNull : public Entity {
public:
  EntityNull() {};
  ~EntityNull() {};
  
  void Update(float dt) override {}
  void OnRender() override {}
  virtual void SetPosition(const Vec2 &pos) {}
  virtual const Vec2& GetPosition() const {return Vec2(0,0);}

  virtual void SetSize(const TextureSize &size) {}
  virtual const TextureSize GetSize() const {return TextureSize(0,0);}
  
  virtual Texture& GetTexture() {}
  bool isPlayer() const override { return false; }

private:
};
#endif // !SnakeGame_ENTITY_NULL_OBJECT_HPP