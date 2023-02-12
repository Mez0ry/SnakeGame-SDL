#ifndef SnakeGame_SNAKE_BODY_HPP
#define SnakeGame_SNAKE_BODY_HPP
#include "../CSDLContext/CSDLContext.hpp"
#include "../SoundManager/SoundManager.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../Map.hpp"
#include "../Entity/Entity.hpp"
#include <deque>

class SnakeBody {
private:
	TextureManager m_SnakeBodyTexture;
	SquareType** m_MapState;
public:
	SnakeBody();
	~SnakeBody();
	void AddLength();
	void Update(SquareType** map_state, EntityPosition& snake_position);
	void Render();
	void Reset();
private:
	const size_t m_maxlength = 10;
	size_t m_CurrSize;
	std::deque<SDL_Rect> rq;
	SDL_Rect m_BodyPosition;
};
#endif // !SnakeGame_SNAKE_BODY_HPP