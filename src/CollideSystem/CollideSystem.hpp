#ifndef SnakeGame_COLLIDE_SYSTEM_HPP
#define SnakeGame_COLLIDE_SYSTEM_HPP
#include "../Observer/Subject/Subject.hpp"
#include "../Entity/Entity.hpp"
class CollideSystem : public Subject{
    public:
    CollideSystem();
    ~CollideSystem();

    bool IsColliding(Entity& ent_lhs, Entity& ent_rhs);
    private:
};
#endif //!SnakeGame_COLLIDE_SYSTEM_HPP