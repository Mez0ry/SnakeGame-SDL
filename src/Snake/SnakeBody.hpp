#ifndef SnakeGame_SNAKE_BODY_HPP
#define SnakeGame_SNAKE_BODY_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../Texture/Texture.hpp"
#include "../Map.hpp"
#include "../Entity/Entity.hpp"
#include <deque>

class SnakeBody {
private:
	Texture m_SnakeBodyTexture;
public:
	SnakeBody();
	~SnakeBody();
	void AddLength();
	void Update(Vec2& snake_position);
	void Render();
	void Reset();

public:
	Texture& GetTexture() {return m_SnakeBodyTexture;}
private:
	const size_t m_maxlength = 10;
	size_t m_CurrSize;
	std::deque<Vec2> m_BodyDq;
};
#endif // !SnakeGame_SNAKE_BODY_HPP