set(SCENE_UTILS_DATA_FIELD ScenesUtils/DataField/DataField.hpp ScenesUtils/DataField/DataField.cpp)
set(SCENE_UTILS_INERTIAL_SCROLL ScenesUtils/InertialScroll/InertialScroll.hpp ScenesUtils/InertialScroll/InertialScroll.cpp)

set(GAME_SCENES_HEADERS CExit.hpp CMatchHistory.hpp CMenu.hpp CPause.hpp CPlaying.hpp GameScene.hpp)
set(GAME_SCENES_SOURCES CExit.cpp CMatchHistory.cpp CMenu.cpp CPause.cpp CPlaying.cpp)

add_library(GameScenes SHARED ${SCENE_UTILS_DATA_FIELD}
                              ${SCENE_UTILS_INERTIAL_SCROLL}  
                              ${GAME_SCENES_HEADERS} 
                              ${GAME_SCENES_SOURCES} 
                              GameScenesController.hpp 
                              GameScenesController.cpp) #! add_library
