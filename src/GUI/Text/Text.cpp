#include "Text.hpp"

Text::Text() noexcept : m_Texture(nullptr), m_font(nullptr)
{
 
}

Text::Text(const char* font_path,int font_size, const char* text,const SDL_Color& color)
{
  LoadFont(font_path,font_size);
  LoadText(text,color);
}

Text::~Text() noexcept
{
  DestroyText();
}
 
void Text::LoadFont(const char *path, int font_size)
{
  TTF_Font* font = TTF_OpenFont(path, font_size);
  m_font = UI::Ref<TTF_Font>(font,TTF_FontDeleter());
  if (m_font == NULL)
  {
    std::cout << "Font can't be opened, Error: " << TTF_GetError() << '\n';
  }
}

void Text::DestroyText()
{
   if (m_Texture.unique())
   {
    SDL_DestroyTexture(m_Texture.get());
    m_Texture = nullptr;
   }
   
}

void Text::LoadText(const char *text, const SDL_Color &color)
{
  if (m_Texture)
    return;

  SDL_Surface * surface = TTF_RenderText_Solid(m_font.get(), text, color);
  if (surface == NULL)
  {
    std::cout << "Can't get surface from font, Error: " << TTF_GetError() << '\n';
  }

  m_Texture = UI::Ref<SDL_Texture>(SDL_CreateTextureFromSurface(CSDLContext::instance().get_renderer(), surface),SDL_TextureDeleter());

  SDL_FreeSurface(surface);
  surface = nullptr;

  if (m_Texture == NULL)
  {
    std::cout << "Can't get font texture from surface , Error: " << TTF_GetError() << '\n';
  }
}

bool Text::CursorIsColliding(const Vec2 &cursor_pos)
{
  return (cursor_pos.x >= m_dst.x && cursor_pos.x <= m_dst.x + m_dst.w && cursor_pos.y >= m_dst.y && cursor_pos.y <= m_dst.y + m_dst.h);
}

void Text::set_Rect(int x, int y, int width, int height)
{
  m_dst.x = x;
  m_dst.y = y;
  m_dst.w = width;
  m_dst.h = height;
  
}

void Text::RenderText()
{
  if (SDL_RenderCopy(CSDLContext::instance().get_renderer(), m_Texture.get(), NULL, &m_dst) != EXIT_SUCCESS)
  {
    std::cout << "Failed to render text, Error: " << SDL_GetError() << '\n';
  }
}

void Text::RenderTextOnTopOfAnother(SDL_Texture *back_texture, SDL_Rect &back_src, SDL_Rect &back_dst)
{
  SDL_SetTextureBlendMode(back_texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(CSDLContext::instance().get_renderer(), back_texture);

  SDL_RenderCopy(CSDLContext::instance().get_renderer(), m_Texture.get(), NULL, &m_dst);

  SDL_SetRenderTarget(CSDLContext::instance().get_renderer(), 0);
  SDL_RenderCopy(CSDLContext::instance().get_renderer(), back_texture, &back_src, &back_dst);
}