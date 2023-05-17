#ifndef SnakeGame_MAP_HPP
#define SnakeGame_MAP_HPP
#include "SDL2/SDL.h"
#include "CAppSettings/CAppSettings.hpp"
#include "Texture/Texture.hpp"
#include "Entity/Entity.hpp"
#include <array>
#include "TextureAnimation/TextureAnimation.hpp"

class Map
{
public:
	Map();
	~Map();
	
    void OnCreate();
	void Render();
	
	//[[nodiscard]] uint8_t** get_MapState() const noexcept { return m_Map; }
	
	static Vec2 GetPositionAt(uint32_t x,uint32_t y, int texture_width, int texture_height){
		Vec2 position;
		position.x = (x * texture_width) + CAppSettings::instance().get_WindowWidth() / CAppSettings::instance().get_MapWidth();
		position.y = (y * texture_height) + CAppSettings::instance().get_WindowHeight() / CAppSettings::instance().get_MapHeight();
		return position;
	}

	static void RenderEntity(Entity& entity){
		if(!IsOnBoard(entity)){
			return;
		}

		const Vec2 &pos = entity.GetPosition();
		auto size = entity.GetSize();
		
		RenderTextureAt(entity.GetTexture(),pos);
		entity.OnRender();
	}

	static void RenderSpriteAnimationAt(TextureAnimation& animation, const Vec2& pos){
		if(!IsOnBoard(pos)){
			return;
		}
		
		TextureSize size = animation.GetTextureSize();
		const Vec2 texture_pos = {m_MapTopLeft.x + pos.x * size.GetWidth(), m_MapTopLeft.y + pos.y * size.GetHeight()};
		animation.SetPosition(texture_pos);
		animation.SetTextureSize(size);
		
		animation.Render();
	}

	/**@brief renders relative to map*/
	static void RenderTextureAt(Texture& texture,const Vec2& pos){
		if(!IsOnBoard(pos)){
			return;
		}
		
		TextureSize size = texture.GetTextureSize();
		const Vec2 texture_pos = {m_MapTopLeft.x + pos.x * size.GetWidth(), m_MapTopLeft.y + pos.y * size.GetHeight()};
		texture.SetTexturePosition(texture_pos);
		texture.SetTextureSize(size);
		
		texture.RenderTexture();
	}

	static bool IsOnBoard(const Vec2 &pos) {
    	return (pos.y < CAppSettings::instance().get_MapHeight() && pos.x < CAppSettings::instance().get_MapWidth() && pos.y > -1 && pos.x > -1);
  	}

	static bool IsOnBoard(const Entity& entity) {
    	return (entity.GetPosition().y < CAppSettings::instance().get_MapHeight() && entity.GetPosition().x < CAppSettings::instance().get_MapWidth() && entity.GetPosition().y > -1 && entity.GetPosition().x > -1);
  	}
	
	void OnResize(){
		int window_w{}, window_h{}; 
		SDL_GetWindowSize(CSDLContext::instance().get_window(),&window_w,&window_h);

        TextureSize square_size = m_MapTexture.GetTextureSize();
        
        m_MapTopLeft.x = (window_w - (square_size.GetWidth() * CAppSettings::instance().get_MapWidth())) * 0.5;
        m_MapTopLeft.y = (window_h - (square_size.GetHeight() * CAppSettings::instance().get_MapHeight())) * 0.5;

        int square_width  = (window_w / CAppSettings::instance().get_MapWidth()) * 0.95;
        int square_height  = (window_h / CAppSettings::instance().get_MapHeight()) * 0.90;
		
        if (square_width > square_height)
            square_width = square_height;
        else{
            square_height = square_width;
		}

		m_MapTexture.SetTextureSize(TextureSize(square_width,square_height));
		for(auto& rounded_corner : m_RoundedCorners){
			rounded_corner.SetTextureSize(TextureSize(square_width,square_height));
		}
	}
	
	TextureSize GetTextureSize() const {
		return m_MapTexture.GetTextureSize();
	}

private:
	Map(const Map&) = delete;
	Map(Map&&) = delete;
	Map& operator=(const Map&) = delete;
	Map& operator=(Map&) = delete;

private:
	uint8_t** m_Map;
	Texture m_MapTexture;

	std::array<Texture,4> m_RoundedCorners;
	Vec2 m_MapSize;
	static Vec2 m_MapTopLeft;
};
#endif //!SnakeGame_MAP_HPP