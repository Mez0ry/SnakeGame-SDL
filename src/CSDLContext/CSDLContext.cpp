#include "CSDLContext.hpp"

CSDLContext::CSDLContext() {}

CSDLContext::~CSDLContext()
{
  SDL_FreeSurface(m_windowSurface);
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);

  SDL_Quit();
  TTF_Quit();
  IMG_Quit();
  Mix_Quit();
}

void CSDLContext::init()
{
  Timer FunctionTimer;
  
  auto& module_context = LOG_INSTANCE["CSDLContext"];
  auto& function_context = module_context.GetMethod(LOG_FUNCTION_NAME);

  if (SDL_Init(SDL_INIT_EVERYTHING) != EXIT_SUCCESS)
  {
    function_context.AddContent("SDL_Init", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR(SDL_GetError()));
    function_context.GetContent("SDL_Init").SetFormat(ContentFormat::SubsystemFormat);
  }
 
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
  {
    function_context.AddContent("IMG_Init", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR(IMG_GetError()));
    function_context.GetContent("IMG_Init").SetFormat(ContentFormat::SubsystemFormat);
  }
 
  if (TTF_Init() != EXIT_SUCCESS)
  {
    function_context.AddContent("TTF_Init", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR(TTF_GetError()));
    function_context.GetContent("TTF_Init").SetFormat(ContentFormat::SubsystemFormat);
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != EXIT_SUCCESS)
  {
    function_context.AddContent("Mix_OpenAudio", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR(Mix_GetError()));
    function_context.GetContent("Mix_OpenAudio").SetFormat(ContentFormat::SubsystemFormat);
  }
 
  uint32_t window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

  if (CAppSettings::instance().get_FullScreen())
  {
    window_flags += SDL_WINDOW_FULLSCREEN;
  }

  m_window = SDL_CreateWindow("SnakeGameSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight(), window_flags);
  
  const auto& SDL_func_format = []() -> ContentFormat::content_format_type_t { 
    ContentFormat::content_format_type_t format; 
    format.push_back("SDL Function: "); 
    format.push_back("Status: "); 
    format.push_back("Line: "); 
    format.push_back("Message: "); 
    return format; 
  };
  
  if (m_window == NULL)
  {
    function_context.AddContent("SDL_CreateWindow", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR((std::string)"Failed to create window, error: " + SDL_GetError()));
    function_context.GetContent("SDL_CreateWindow").SetFormat(SDL_func_format);
  }
  
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  if (m_renderer == NULL)
  {
    function_context.AddContent("SDL_CreateRenderer", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR((std::string)"Failed to create renderer, error: " + SDL_GetError()));
    function_context.GetContent("SDL_CreateRenderer").SetFormat(SDL_func_format);
  }
  
  m_windowSurface = SDL_GetWindowSurface(m_window);
  
  if (m_windowSurface == NULL)
  {
    function_context.AddContent("SDL_GetWindowSurface", MESSAGE_ERROR("Failure"),MessageModel(LOG_CURRENT_LINE), MESSAGE_ERROR((std::string)"Failed to get window surface, error: " + SDL_GetError()));
    function_context.GetContent("SDL_GetWindowSurface").SetFormat(SDL_func_format);
  }

  function_context.SetExecutionTime(FunctionTimer.GetDurationInSeconds(),"sec");
  LOG_INSTANCE.PrintModule(module_context);
}

CSDLContext &CSDLContext::instance()
{
  static CSDLContext instance;
  return instance;
}