#ifndef SnakeGame_FONT_MANAGER_HPP
#define SnakeGame_FONT_MANAGER_HPP
#include "../../CSDLContext/CSDLContext.hpp"

#include "../../Vector.hpp"
#include "../../Base.hpp"

#include "SDL2/SDL_ttf.h"
#include <bitset>
#include <iostream>
#include <string_view>
#include "../../Texture/Texture.hpp"

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
    this->m_font = std::move(other.m_font);
    this->m_Texture = std::move(other.m_Texture);
    this->m_Color = std::move(other.m_Color);
  }

  Text& operator=(const Text& other){
    if(this == &other){
      return (*this);
    }
    this->m_font = other.m_font;
    this->m_Texture = other.m_Texture;

    this->m_Color = other.m_Color;
    return (*this);
  }

  Text& operator=(Text&& other){
    if(this == &other){
      return (*this);
    }
    this->m_font = std::move(other.m_font);
    this->m_Texture = std::move(other.m_Texture);
    this->m_Color = std::move(other.m_Color);
    return (*this);
  }
  
  Texture* operator->(){
    return &m_Texture;
  }

  Base::Ref<TTF_Font> LoadFont(const char *path, int font_size);
  Texture& LoadText(const char *text, const SDL_Color &color);

  void ShareFont(Base::Ref<TTF_Font>&& font);
  void Reset();
  void ResetFont();

  void RenderText();

  Texture& GetTextTexture() {return m_Texture;}
  const Texture& GetTextTexture() const {return m_Texture;}

private:
  Base::Ref<TTF_Font> m_font;
  Texture m_Texture;
  SDL_Color m_Color;
};
#endif //! SnakeGame_FONT_MANAGER_HPP