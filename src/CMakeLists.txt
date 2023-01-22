set(EXECUTABLE_NAME SnakeGameSDL)

add_subdirectory(CAppSettings)
add_subdirectory(CSDLContext)
add_subdirectory(Timer)
add_subdirectory(TextureManager)
add_subdirectory(SpriteAnimation)
add_subdirectory(SoundManager)
add_subdirectory(FontManager)
add_subdirectory(Food)
add_subdirectory(Snake)
add_subdirectory(Observer)
add_subdirectory(Logger)
add_subdirectory(GameScenes)
add_subdirectory(AchievementSystem)
add_subdirectory(CollideSystem)
add_subdirectory(GameScore)

include_directories({PROJECT_SOURCE_DIR}/Serializer)
include_directories({PROJECT_SOURCE_DIR}/Entity)

add_executable(${EXECUTABLE_NAME} main.cpp Game.hpp Game.cpp Map.hpp Map.cpp)

target_link_libraries(${EXECUTABLE_NAME} CAppSettings
                          CSDLContext 
                          Timer 
                          TextureManager 
                          SpriteAnimation 
                          SoundManager 
                          FontManager 
                          Food 
                          Snake 
                          Observer 
                          Logger 
                          GameScenes 
                          AchievementSystem 
                          CollideSystem 
                          GameScore)

##Vendor
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory(../vendor/SDL ../sdl_build)
target_link_libraries(${EXECUTABLE_NAME} SDL2)

add_subdirectory(../vendor/SDL_image ../sdl_image_build)
target_link_libraries(${EXECUTABLE_NAME} SDL2_image)

add_subdirectory(../vendor/SDL_ttf ../sdl_ttf_build)
target_link_libraries(${EXECUTABLE_NAME} SDL2_ttf)

set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)

add_subdirectory(../vendor/SDL_mixer ../sdl_mixer_build)
target_link_libraries(${EXECUTABLE_NAME} SDL2_mixer)