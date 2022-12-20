#ifndef SnakeGame_TEXTURE_MANAGER_HPP
#define SnakeGame_TEXTURE_MANAGER_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../CSDLContext/CSDLContext.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>

#include "../FontManager/FontManager.hpp" // need CursorPosition POD

enum class ImageType { PNG, BMP };

namespace TextureConstants {
constexpr int TextureWidth = 32;
constexpr int TextureHeight = 32;

}; // !namespace TextureConstants

class TextureManager {
public:
  TextureManager();
  ~TextureManager();

  void LoadTexture(const std::string& path, ImageType type = ImageType::PNG);
  void set_Texture(SDL_Texture* texture);
  void DestroyTexture();
  void ReloadTexture();

  void set_TextureAlphaMod(uint8_t alpha);
  void set_srcRect(int x, int y, int w = TextureConstants::TextureWidth, int h = TextureConstants::TextureHeight);
  void set_dstRect(int x, int y, int w = TextureConstants::TextureWidth, int h = TextureConstants::TextureHeight);

  void set_SelectStatus(bool select_status) { this->m_Selected[0] = select_status; }

  SDL_Rect &get_srcRect() { return m_src; }
  SDL_Rect &get_dstRect() { return m_dst; }

  SDL_Rect get_srcRect() const { return m_src; }
  SDL_Rect get_dstRect() const { return m_dst; }
  [[nodiscard]] SDL_Texture *get_Texture() { return m_texture; }

  bool CursorIsColliding(const CursorPosition &cursor_pos);

  void RenderTexture();
public:
  void AdditionAssignmentToDstRect(int x,int y, int w , int h);
  void SubtractionAssignmentToDstRect(int x,int y,int w,int h);

  void AdditionAssignmentToSrcRect(int x,int y, int w , int h);
  void SubtractionAssignmentToSrcRect(int x,int y,int w,int h);
private:
  SDL_Rect m_src, m_dst;
  SDL_Texture *m_texture;
  std::string m_TexturePath;
  ImageType m_ImageType;
  std::bitset<1> m_Selected;
};
#endif //! SnakeGame_TEXTURE_MANAGER_HPP