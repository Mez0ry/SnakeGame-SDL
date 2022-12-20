#ifndef SnakeGame_MAP_HPP
#define SnakeGame_MAP_HPP
#include "SDL2/SDL.h"
#include "CAppSettings/CAppSettings.hpp"
#include "TextureManager/TextureManager.hpp"

enum class SquareType {
	BACKGROUND, ENTITY, UNKNOWN
};

namespace MapUtils{
 inline int CorrectWidthPosOnTheMap(const int pos_x){ return ( pos_x * TextureConstants::TextureWidth + CAppSettings::instance().get_WindowWidth() / CAppSettings::instance().get_MapWidth());}
 inline int CorrectHeightPosOnTheMap(const int pos_y){ return ( pos_y * TextureConstants::TextureHeight + CAppSettings::instance().get_WindowHeight() / CAppSettings::instance().get_MapHeight());}	
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
	TextureManager m_MapTexture;
};
#endif //!SnakeGame_MAP_HPP