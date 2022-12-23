#ifndef SnakeGame_GameScenes_CSTATS_HPP
#define SnakeGame_GameScenes_CSTATS_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../CSDLContext/CSDLContext.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../FontManager/FontManager.hpp"
#include "GameScene.hpp"
#include <climits>

typedef struct InertialScrollModel
{
    int scrolling;              // flag (scrolling or not)
    int scroll_sensitivity = 5; // how fast we want to scroll
    double scroll_y = 0;        // current scrolling amount (on Y-Axis)
    double scroll_acceleration; // scrolling speed
    double scroll_friction = 2; // how fast we decelerate
    double scroll_prev_pos;
} InertialScrollModel;

class CMatchHistory : public GameScene
{
public:
    CMatchHistory();
    ~CMatchHistory();

    void OnCreate() override;
    void BeforeDestruction() override;
    void OnDestroy() override;

    void InputHandler() override;
    void Update() override;
    void Render() override;

private:
    TextureManager m_ReturnButton;
    TextureManager m_BackgroundTexture;
    TextureManager m_DataFieldTexture;
    TextureManager m_MatchBoardTexture;
    
    InertialScrollModel m_InertialScrollModel;

private:

template < typename std::size_t Row_Size, typename std::size_t Col_Size>
constexpr int ClosestTextureResolution(int texture_resolution_arr[Row_Size][Col_Size], int row, int col);
};
#endif //! SnakeGame_GameScenes_CSTATS_HPP