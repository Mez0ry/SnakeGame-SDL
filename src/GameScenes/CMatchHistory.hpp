#ifndef SnakeGame_GameScenes_CSTATS_HPP
#define SnakeGame_GameScenes_CSTATS_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../CSDLContext/CSDLContext.hpp"
#include "../TextureManager/TextureManager.hpp"
#include "../FontManager/FontManager.hpp"
#include "GameScene.hpp"
#include <climits>
#include "ScenesUtils/DataField/DataField.hpp"
#include "ScenesUtils/InertialScroll/InertialScroll.hpp"
#include <queue>

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
    TextureManager m_MatchBoardTexture;

    InertialScroll m_InertialScroll;
    DataField *m_DataFields;
    std::queue<int> m_ScoreQueue;
    std::queue<double> m_InGameTime;

    int m_FieldsSize = 0;
private:
    

    template <typename std::size_t Row_Size, typename std::size_t Col_Size>
    constexpr int ClosestTextureResolution(int texture_resolution_arr[Row_Size][Col_Size], int row, int col);
};
#endif //! SnakeGame_GameScenes_CSTATS_HPP