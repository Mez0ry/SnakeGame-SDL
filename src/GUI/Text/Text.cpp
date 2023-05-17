#include "Text.hpp"

Text::Text() noexcept : m_font(nullptr)
{
 
}

Text::Text(const char* font_path,int font_size, const char* text,const SDL_Color& color)
{
  LoadFont(font_path,font_size);
  LoadText(text,color);
}

Text::~Text() noexcept
{
   Reset();
}
 
GUI::Ref<TTF_Font> Text::LoadFont(const char *path, int font_size)
{
  TTF_Font* font = TTF_OpenFont(path, font_size);
  m_font = GUI::Ref<TTF_Font>(font,TTF_FontDeleter());
  if (m_font == NULL)
  {
    std::cout << "Font can't be opened, Error: " << TTF_GetError() << '\n';
  }
  return m_font;
}

Texture& Text::LoadText(const char *text, const SDL_Color &color)
{
  Reset();

  SDL_Surface * surface = TTF_RenderText_Solid(m_font.get(), text, color);
  if (surface == NULL)
  {
    std::cout << "Can't get surface from font, Error: " << TTF_GetError() << '\n';
  }
  
  m_Texture.ShareSDLTexture(Texture::CreateTextureFromSurface(surface));

  SDL_FreeSurface(surface);
  surface = nullptr;

  if (!m_Texture)
  {
    std::cout << "Can't get font texture from surface , Error: " << TTF_GetError() << '\n';
  }
  return m_Texture;
}

void Text::ShareFont(GUI::Ref<TTF_Font>&& font)
{
  this->m_font = std::move(font);
}

void Text::Reset()
{
  m_Texture.Reset();
}

void Text::ResetFont()
{
  if(m_font.unique()){
    m_font.reset();
    m_font = nullptr;
  }

}

void Text::RenderText()
{
  m_Texture.RenderTexture();
}