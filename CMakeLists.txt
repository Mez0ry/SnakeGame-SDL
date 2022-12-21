cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(ProjectName SnakeGameSDL)

project(${ProjectName})

set(RootSources src/main.cpp src/Map.cpp src/Game.cpp)
set(RootHeaders src/Map.hpp src/Game.hpp)

message("Root SOURCES: ${RootSources}\n")
message("Root HEADERS: ${RootHeaders}\n")

add_executable(${ProjectName} ${RootSources} ${RootHeaders})

add_subdirectory(src/CSDLContext)
add_subdirectory(src/CAppSettings)
add_subdirectory(src/CollideSystem)
add_subdirectory(src/FontManager)
add_subdirectory(src/Food)
add_subdirectory(src/GameScenes)
add_subdirectory(src/GameScore)

add_subdirectory(src/Observer)
add_subdirectory(src/AchievementSystem)
add_subdirectory(src/Snake)

add_subdirectory(src/SoundManager)
add_subdirectory(src/SpriteAnimation)
add_subdirectory(src/TextureManager)
add_subdirectory(src/Timer)

##Vendor
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/SDL)
target_link_libraries(${ProjectName} SDL)

add_subdirectory(vendor/SDL_image)
target_link_libraries(${ProjectName} SDL_image)

add_subdirectory(vendor/SDL_ttf)
target_link_libraries(${ProjectName} SDL_ttf)

set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)

add_subdirectory(vendor/SDL_mixer)
target_link_libraries(${ProjectName} SDL_mixer)