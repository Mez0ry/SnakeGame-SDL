#ifndef SnakeGame_GameScenes_CSTATS_HPP
#define SnakeGame_GameScenes_CSTATS_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../CSDLContext/CSDLContext.hpp"
#include "../Texture/Texture.hpp"
#include "GameScene.hpp"
#include <climits>
#include "../GUI/Text/Text.hpp"
#include "../GUI/UIElements/Datafield.hpp"
#include "../GUI/InertialScroll/InertialScroll.hpp"
#include "../Serializer/Serializer.hpp"
#include "../Vector.hpp"
#include <vector>

class CMatchHistory : public GameScene
{
public:
    CMatchHistory();
    ~CMatchHistory();

    void OnCreate() override;
    void BeforeDestruction() override {}
    void OnDestroy() override;
    
    void InputHandler() override;
    void Update() override;
    void Render() override;

private:
    Texture m_ReturnButton;
    Texture m_BackgroundTexture;
    Texture m_MatchBoardTexture;

    InertialScroll m_InertialScroll;
    
    std::vector<Datafield> m_DataFields;
    std::vector<int> m_ScoreVec;
    std::vector<double> m_InGameTimeVec;
};
#endif //! SnakeGame_GameScenes_CSTATS_HPP