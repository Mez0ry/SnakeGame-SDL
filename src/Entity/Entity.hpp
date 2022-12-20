#ifndef SnakeGame_ENTITY_HPP
#define SnakeGame_ENTITY_HPP
typedef struct EntityPosition{
  int x,y;
};

class Entity {
public:
  virtual ~Entity() {}

  virtual void Update() = 0;
  virtual void Render() = 0;

  virtual const EntityPosition& get_PositionOnMap() const  = 0;
  virtual bool isPlayer() const { return false;}
private:
};
#endif //! SnakeGame_ENTITY_HPP