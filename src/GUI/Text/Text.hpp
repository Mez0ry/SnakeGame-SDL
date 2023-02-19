#ifndef SnakeGame_FONT_MANAGER_HPP
#define SnakeGame_FONT_MANAGER_HPP
#include "../../CSDLContext/CSDLContext.hpp"

#include "../../Vector.hpp"
#include "../base.hpp"
#include "SDL2/SDL_ttf.h"
#include <bitset>
#include <iostream>
#include <string_view>

struct SDL_TextureDeleter {
  void operator()(SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
};

struct TTF_FontDeleter {
  void operator()(TTF_Font *font) {
    if (font != nullptr) {
      TTF_CloseFont(font);
      font = nullptr;
    }
  }
};

class Text {
public:
  Text() noexcept;
  Text(const char *font_path, int font_size, const char *text, const SDL_Color &color);
  ~Text() noexcept;

  Text(Text &&other) {
    this->m_font = other.m_font;
    this->m_Texture = other.m_Texture;
    this->m_dst = std::move(other.m_dst);
    this->m_Color = std::move(other.m_Color);
    this->m_Selected = std::move(other.m_Selected);
  }

  Text& operator=(const Text& other){
    this->m_font = other.m_font;
    this->m_Texture = other.m_Texture;
    this->m_dst = other.m_dst;
    this->m_Color = other.m_Color;
    this->m_Selected = other.m_Selected;
    return (*this);
  }

  Text& operator=(Text&& other){
    this->m_font = other.m_font;
    this->m_Texture = other.m_Texture;
    this->m_dst = std::move(other.m_dst);
    this->m_Color = std::move(other.m_Color);
    this->m_Selected = std::move(other.m_Selected);
    return (*this);
  }
  
  void LoadFont(const char *path, int font_size);

  const SDL_Rect &get_Rect() const { return m_dst; }
  void set_Rect(const SDL_Rect &rect) { m_dst = std::move(rect); }
  void set_Rect(int x, int y, int width, int height);

  void DestroyText();
  void LoadText(const char *text, const SDL_Color &color);

  [[nodiscard]] SDL_Texture *get_Texture() const { return m_Texture.get(); }

  void RenderText();

  void RenderTextOnTopOfAnother(SDL_Texture *back_texture, SDL_Rect &back_src, SDL_Rect &back_dst);

  bool CursorIsColliding(const Vec2 &cursor_pos);
  bool isSelected() const { return m_Selected[0]; }
  void set_SelectStatus(bool state) { this->m_Selected[0] = state; }

private:
  UI::Ref<TTF_Font> m_font;
  UI::Ref<SDL_Texture> m_Texture;
  SDL_Rect m_dst;
  SDL_Color m_Color;
  std::bitset<1> m_Selected;
};
#endif //! SnakeGame_FONT_MANAGER_HPP