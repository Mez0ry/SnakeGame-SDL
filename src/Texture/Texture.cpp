#include "Texture.hpp"

Texture::Texture() : m_texture(nullptr) {}

Texture::~Texture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

SDL_Texture *Texture::LoadTexture(const std::string &path) {
  if (m_texture != nullptr)
    return m_texture;

  SDL_Surface *tmp_surface = nullptr;

  tmp_surface = IMG_Load(path.c_str());
  if (tmp_surface == NULL) {
    std::cout << "Can't load texture, Error: " << IMG_GetError() << '\n';
  }

  m_texture = SDL_CreateTextureFromSurface(CSDLContext::instance().get_renderer(), tmp_surface);

  if (m_texture == NULL) {
    std::cout << "Can't Create texture from surface, Error: " << SDL_GetError() << '\n';
  }

  SDL_FreeSurface(tmp_surface);
  return (m_texture == NULL) ? nullptr : m_texture;
}

void Texture::set_Texture(SDL_Texture *texture) { this->m_texture = texture; }

void Texture::RenderTexture() {
  if (SDL_RenderCopy(CSDLContext::instance().get_renderer(), m_texture, &m_src, &m_dst) != EXIT_SUCCESS) {
    std::cout << "Texture cant Render texture, Error: " << SDL_GetError() << '\n';
  }
}

void Texture::DestroyTexture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
  }
}

void Texture::set_TextureAlphaMod(uint8_t alpha) {
  SDL_SetTextureAlphaMod(m_texture, alpha);
}

bool Texture::CursorIsColliding(const Vec2 &cursor_pos) {
  return (cursor_pos.x >= m_dst.x && cursor_pos.x <= m_dst.x + m_dst.w && cursor_pos.y >= m_dst.y && cursor_pos.y <= m_dst.y + m_dst.h);
}