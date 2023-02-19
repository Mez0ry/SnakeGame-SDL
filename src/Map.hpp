#ifndef SnakeGame_MAP_HPP
#define SnakeGame_MAP_HPP
#include "SDL2/SDL.h"
#include "CAppSettings/CAppSettings.hpp"
#include "Texture/Texture.hpp"

enum class SquareType {
	BACKGROUND, ENTITY, UNKNOWN
};

class Map
{
public:
	Map();
	~Map();
	
    void OnCreate();
	void Render();
	
	[[nodiscard]] SquareType** get_MapState() const noexcept { return m_Map; }
private:
	Map(const Map&) = delete;
	Map(Map&&) = delete;
	Map& operator=(const Map&) = delete;
	Map& operator=(Map&) = delete;

private:
	SquareType** m_Map;
	Texture m_MapTexture;
};
#endif //!SnakeGame_MAP_HPP