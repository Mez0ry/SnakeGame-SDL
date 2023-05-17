#ifndef SnakeGame_GAME_HPP
#define SnakeGame_GAME_HPP
#include "CSDLContext/CSDLContext.hpp"
#include "GameScenes/GameScenesController.hpp"

typedef struct CustomCursor {
  CustomCursor() : m_Cursor(nullptr){}
  ~CustomCursor() { if(m_Cursor != nullptr) SDL_FreeCursor(m_Cursor);}

  void LoadCursor(const std::string &cursor_path) {
    auto& module_context = LOG_INSTANCE["CustomCursor"];
    auto& function_context = module_context.GetMethod(LOG_FUNCTION_NAME);
    SDL_Surface *cursor_surface = IMG_Load(cursor_path.c_str());
    if(cursor_surface == NULL){
       function_context.AddContent("if(cursor_surface == NULL)",MESSAGE_ERROR("Failure"), MessageModel(LOG_CURRENT_LINE),MESSAGE_ERROR(IMG_GetError()) );
       function_context.GetContent("if(cursor_surface == NULL)").SetFormat(ContentFormat::ExpressionFormat);
    }
    m_Cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);
    SDL_SetCursor(m_Cursor);
    SDL_FreeSurface(cursor_surface);
    LOG_INSTANCE.PrintModule(module_context);
  }

private:
  SDL_Cursor *m_Cursor;
};

class Game {
private:
  uint32_t m_fps = 60;
  float m_frameDelay = 3000 / m_fps;
  bool m_bGameLoop = false;

public:
  Game();
  ~Game();
  void Run();

  void InputHandler();
  void Update(float dt);
  void Render();
private:
  Uint32 GetDeltaTime(Uint32 previous,float offset);
private:
  GameScenesController m_ScenesController;
  CustomCursor m_CustomCursor;
};
#endif //! SnakeGame_GAME_HPP