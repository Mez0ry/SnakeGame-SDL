#include "Texture.hpp"

Texture::Texture() noexcept : m_texture(nullptr) {}

Texture::Texture(const std::string& texture_path) : m_texture(nullptr) {
  LoadTexture(texture_path);
}

Texture::~Texture() noexcept{
  Reset();
}

Base::Ref<SDL_Texture> Texture::LoadTexture(const std::string &path) {
  Reset();
  
  SDL_Surface *tmp_surface = nullptr;

  tmp_surface = IMG_Load(path.c_str());
  if (tmp_surface == NULL) {
    std::cout << "Can't load texture, Error: " << IMG_GetError() << '\n';
  }

  m_texture = Texture::CreateTextureFromSurface(tmp_surface);
  if (m_texture == nullptr) {
    std::cout << "Can't Create texture from surface, Error: " << SDL_GetError() << '\n';
  }

  SDL_FreeSurface(tmp_surface);

  return (m_texture == nullptr ) ? nullptr : m_texture;
}

Base::Ref<SDL_Texture> Texture::CreateTextureFromSurface(SDL_Surface* surface){
  return std::move(Base::Ref<SDL_Texture>(SDL_CreateTextureFromSurface(CSDLContext::instance().get_renderer(), surface),TextureDeleter()));
}

void Texture::ShareSDLTexture(const Texture& texture) {
  Reset();

  m_texture = texture.m_texture;
}

void Texture::ShareSDLTexture(const Base::Ref<SDL_Texture> & texture) {
  Reset();

  m_texture = texture;
}

void Texture::RenderTexture() {
  if (SDL_RenderCopy(CSDLContext::instance().get_renderer(), m_texture.get(), &m_src, &m_dst) != EXIT_SUCCESS) {
    std::cout << "Can't render texture, Error: " << SDL_GetError() << '\n';
  }
}

void Texture::Reset() {
  if (m_texture != nullptr) {
    m_texture.reset();
    m_texture = nullptr;
  }
}

bool Texture::PointIsOnTexture(const Vec2 &point) const{
  return (point.x >= top_left().x && point.x <= top_right().x && point.y >= top_left().y && point.y <= bottom_left().y);
}