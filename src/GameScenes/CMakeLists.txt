cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set(GameScenes_Sources CExit.cpp CMenu.cpp CPause.cpp CPlaying.cpp CStats.cpp GameScenesController.cpp)
set(GameScenes_Headers CExit.hpp CMenu.hpp CPause.hpp CPlaying.hpp CStats.hpp GameScene.hpp GameScenesController.hpp)

add_executable(GameScenes ${GameScenes_Sources} ${GameScenes_Headers})
target_include_directories(GameScenes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(GameScenes PROPERTIES LINKER_LANGUAGE CXX)