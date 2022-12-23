cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(ProjectName SnakeGameSDL)

project(${ProjectName})

set (CMAKE_CXX_STANDARD 17)

set(RootSources src/main.cpp src/Map.cpp src/Game.cpp)
set(RootHeaders src/Map.hpp src/Game.hpp)

set(CSDLContext src/CSDLContext/CSDLContext.hpp  src/CSDLContext/CSDLContext.cpp)

set(CAppSettings src/CAppSettings/CAppSettings.hpp src/CAppSettings/CAppSettings.cpp )

set(CollideSystem src/CollideSystem/CollideSystem.hpp src/CollideSystem/CollideSystem.cpp )

set(FontManager src/FontManager/FontManager.hpp src/FontManager/FontManager.cpp)

set(FoodFlyweight src/Food/FoodFlyweight/FoodFlyweight.hpp src/Food/FoodFlyweight/FoodFlyweight.cpp)
set(Food src/Food/Food.hpp src/Food/Food.cpp ${FoodFlyweight})

set(GameScenes src/GameScenes/CExit.hpp src/GameScenes/CExit.cpp src/GameScenes/CMenu.hpp src/GameScenes/CMenu.cpp src/GameScenes/CPause.hpp src/GameScenes/CPause.cpp  src/GameScenes/CPlaying.hpp src/GameScenes/CPlaying.cpp src/GameScenes/CMatchHistory.hpp src/GameScenes/CMatchHistory.cpp src/GameScenes/GameScene.hpp src/GameScenes/GameScenesController.hpp  src/GameScenes/GameScenesController.cpp)

set(GameScore src/GameScore/GameScore.hpp src/GameScore/GameScore.cpp)

set(ObserverSubject src/Observer/Subject/Subject.hpp src/Observer/Subject/Subject.cpp)
set(ObserverEvents src/Observer/ObserverEvents.hpp)
set(Observer src/Observer/Observer.hpp ${ObserverSubject} ${ObserverEvents})

set(AchievementsImpl src/AchievementSystem/Achievements/FiveHundredScore.hpp src/AchievementSystem/Achievements/FiveHundredScore.cpp src/AchievementSystem/Achievements/OneHundredScore.hpp src/AchievementSystem/Achievements/OneHundredScore.cpp src/AchievementSystem/Achievements/OneThousandScore.hpp src/AchievementSystem/Achievements/OneThousandScore.cpp)
set(AchievementSettings src/AchievementSystem/AchievementSettings/AchievementSettings.hpp src/AchievementSystem/AchievementSettings/AchievementSettings.cpp)
set(AchievementSystem ${AchievementSettings} ${AchievementsImpl} src/AchievementSystem/AchievementSystem.hpp src/AchievementSystem/AchievementSystem.cpp src/AchievementSystem/Achievement.hpp)

set(SnakeStates src/Snake/SnakeStates/IdleState.hpp src/Snake/SnakeStates/IdleState.cpp src/Snake/SnakeStates/MovingState.hpp src/Snake/SnakeStates/MovingState.cpp src/Snake/SnakeStates/SnakeStatesController.hpp src/Snake/SnakeStates/SnakeStatesController.cpp)
set(Snake src/Snake/Snake.hpp src/Snake/Snake.cpp src/Snake/SnakeBody.hpp src/Snake/SnakeBody.cpp src/Snake/ISnakeStates.hpp ${SnakeStates} )

set(SoundManager src/SoundManager/SoundManager.hpp src/SoundManager/SoundManager.cpp )

set(SpriteAnimation src/SpriteAnimation/SpriteAnimation.hpp src/SpriteAnimation/SpriteAnimation.cpp)

set(TextureManager src/TextureManager/TextureManager.hpp src/TextureManager/TextureManager.cpp)

set(Timer src/Timer/Timer.hpp src/Timer/Timer.cpp)

message("Root SOURCES: ${RootSources}\n")
message("Root HEADERS: ${RootHeaders}\n")

add_executable(${ProjectName} ${RootSources} ${RootHeaders} ${CSDLContext} ${CAppSettings} ${CollideSystem} ${FontManager} ${Food}  ${GameScenes} ${GameScore} ${Observer} ${AchievementSystem} ${Snake} ${SoundManager} ${SpriteAnimation} ${TextureManager} ${Timer})

##Vendor
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/SDL)
target_link_libraries(${ProjectName} SDL2)

add_subdirectory(vendor/SDL_image)
target_link_libraries(${ProjectName} SDL2_image)

add_subdirectory(vendor/SDL_ttf)
target_link_libraries(${ProjectName} SDL2_ttf)

set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)

add_subdirectory(vendor/SDL_mixer)
target_link_libraries(${ProjectName} SDL2_mixer)