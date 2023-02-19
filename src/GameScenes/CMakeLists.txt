set(GAME_SCENES_HEADERS CExit.hpp CMatchHistory.hpp CMenu.hpp CPause.hpp CPlaying.hpp GameScene.hpp)
set(GAME_SCENES_SOURCES CExit.cpp CMatchHistory.cpp CMenu.cpp CPause.cpp CPlaying.cpp)

add_library(GameScenes SHARED ${GAME_SCENES_HEADERS} 
                              ${GAME_SCENES_SOURCES} 
                              GameScenesController.hpp 
                              GameScenesController.cpp)