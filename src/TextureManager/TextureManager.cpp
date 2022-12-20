#include "TextureManager.hpp"

TextureManager::TextureManager() : m_texture(nullptr) {}

TextureManager::~TextureManager() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

void TextureManager::LoadTexture(const std::string& path, ImageType type /*= ImageType::PNG*/) {
  if (m_texture != nullptr) return;

  SDL_Surface* tmp_surface = nullptr;
  switch (type) {
    case ImageType::PNG: {
      tmp_surface = IMG_Load(path.c_str());
      if (tmp_surface == NULL) {
        std::cout << "Can't load texture, Error: " << IMG_GetError() << '\n';
      }
      break;
    }
    case ImageType::BMP: {
      tmp_surface = SDL_LoadBMP(path.c_str());
      if (tmp_surface == NULL) {
        std::cout << "Can't load texture, Error: " << SDL_GetError() << '\n';
      }
      break;
    }
  }

  m_texture = SDL_CreateTextureFromSurface(CSDLContext::instance().get_renderer(), tmp_surface);

  if (m_texture == NULL) {
    std::cout << "Can't Create texture from surface, Error: " << SDL_GetError() << '\n';
  }

  SDL_FreeSurface(tmp_surface);
  this->m_TexturePath = path;
  this->m_ImageType = type;
}

void TextureManager::set_Texture(SDL_Texture* texture)
{
  this->m_texture = texture;
}

void TextureManager::set_srcRect(int x, int y,int w /**= TextureConstants::TextureWidth*/, int h /**= TextureConstants::TextureHeight*/) {
  m_src.x = x;
  m_src.y = y;
  m_src.w = w;
  m_src.h = h;
}

void TextureManager::set_dstRect(int x, int y, int w /**= TextureConstants::TextureWidth*/, int h /**= TextureConstants::TextureHeight*/) {
  m_dst.x = x;
  m_dst.y = y;
  m_dst.w = w;
  m_dst.h = h;
}

void TextureManager::RenderTexture() {
  if(SDL_RenderCopy(CSDLContext::instance().get_renderer(), m_texture, &m_src, &m_dst) != EXIT_SUCCESS){
    std::cout<<"TextureManager cant Render texture, Error: " << SDL_GetError() << '\n';
  }
}

void TextureManager::AdditionAssignmentToDstRect(int x,int y, int w , int h)
{
  m_dst.x += x;
  m_dst.y += y;
  m_dst.w += w;
  m_dst.h += h;
}

void TextureManager::SubtractionAssignmentToDstRect(int x,int y,int w,int h)
{
  m_dst.x -= x;
  m_dst.y -= y;
  m_dst.w -= w;
  m_dst.h -= h;
}

void TextureManager::AdditionAssignmentToSrcRect(int x,int y, int w , int h)
{
  m_src.x += x;
  m_src.y += y;
  m_src.w += w;
  m_src.h += h;
}

void TextureManager::SubtractionAssignmentToSrcRect(int x,int y,int w,int h)
{
  m_src.x -= x;
  m_src.y -= y;
  m_src.w -= w;
  m_src.h -= h;
}

void TextureManager::DestroyTexture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
  }
}

void TextureManager::ReloadTexture() {
  LoadTexture(m_TexturePath, m_ImageType);
}
void TextureManager::set_TextureAlphaMod(uint8_t alpha) {
  SDL_SetTextureAlphaMod(m_texture, alpha);
}

bool TextureManager::CursorIsColliding(const CursorPosition &cursor_pos)
{
  return (cursor_pos.x >= m_dst.x && cursor_pos.x <= m_dst.x + m_dst.w && cursor_pos.y >= m_dst.y && cursor_pos.y <= m_dst.y + m_dst.h);
}