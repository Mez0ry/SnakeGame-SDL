#ifndef SnakeGame_TEXTURE_MANAGER_HPP
#define SnakeGame_TEXTURE_MANAGER_HPP
#include "../CSDLContext/CSDLContext.hpp"

#include <string>
#include<iostream>
#include "../Vector.hpp" 

/**@brief Used in tag dispatching*/
struct SourceRect {};
struct DestRect {};

class Texture {
private:
public:
  Texture();
  ~Texture();

  SDL_Texture * LoadTexture(const std::string &path);
  void set_Texture(SDL_Texture *texture);
  void DestroyTexture();
  
  void set_TextureAlphaMod(uint8_t alpha);

  template <typename T = DestRect> 
  void set_Rect(int x, int y, int w, int h) {
    static_assert((std::is_same<T, SourceRect>::value || std::is_same<T, DestRect>::value) && "template argument is neither SourceRect nor DestRect ");
    if constexpr (std::is_same<T, SourceRect>::value) {
      m_src.x = x;
      m_src.y = y;
      m_src.w = w;
      m_src.h = h;

    } else if constexpr (std::is_same<T, DestRect>::value) {
      m_dst.x = x;
      m_dst.y = y;
      m_dst.w = w;
      m_dst.h = h;
    }
  }

  template <typename T = DestRect> 
  SDL_Rect &get_Rect() {
    static_assert((std::is_same<T, SourceRect>::value || std::is_same<T, DestRect>::value) && "template argument is neither SourceRect nor DestRect ");
    if constexpr (std::is_same<T, SourceRect>::value) {
      return m_src;
    } else if constexpr (std::is_same<T, DestRect>::value) {
      return m_dst;
    }
  }

  [[nodiscard]] SDL_Texture *get_Texture() { return m_texture; }

  bool CursorIsColliding(const Vec2 &cursor_pos);

  void RenderTexture();

private:
  SDL_Rect m_src, m_dst;
  SDL_Texture *m_texture;
};
#endif //! SnakeGame_TEXTURE_MANAGER_HPP