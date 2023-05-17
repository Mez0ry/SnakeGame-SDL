#ifndef SnakeGame_ENTITY_HPP
#define SnakeGame_ENTITY_HPP
#include "../Vector.hpp"
#include "../Texture/Texture.hpp"

class TextureSize;
class Texture;
class Vec2;

class Entity {
public:
  virtual ~Entity() {}

  virtual void Update(float dt) = 0;
  virtual void OnRender() { }
  
  virtual void SetPosition(const Vec2 &pos) = 0;
  virtual const Vec2& GetPosition() const = 0;

  virtual void SetSize(const TextureSize &size) = 0;
  virtual const TextureSize GetSize() const = 0;
  
  virtual Texture& GetTexture() = 0;
  
  virtual bool isPlayer() const { return false;}
private:
};
#endif //! SnakeGame_ENTITY_HPP