#ifndef SnakeGame_CSDL_CONTEXT_HPP
#define SnakeGame_CSDL_CONTEXT_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "../Timer/Timer.hpp"
#include "../Logger/Logger.hpp"

class CSDLContext {
public:
  CSDLContext();
  ~CSDLContext();

  void init();
  static CSDLContext &instance();

public:
  [[nodiscard]] SDL_Renderer *get_renderer() const { return m_renderer; }
  [[nodiscard]] SDL_Window *get_window() const { return m_window; }
  [[nodiscard]] SDL_Surface *get_WindowSurface() const { return m_windowSurface; }

public:
  CSDLContext(CSDLContext &&) = delete;
  CSDLContext(const CSDLContext &) = delete;
  CSDLContext &operator=(const CSDLContext &) = delete;
  CSDLContext &operator=(CSDLContext &&) = delete;

private:
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
  SDL_Surface *m_windowSurface;
};
#endif //! SnakeGame_CSDL_CONTEXT_HPP