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
#include <queue>
#include "../Serializer/Serializer.hpp"
#include "../Vector.hpp"

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
    Datafield *m_DataFields;
    std::queue<int> m_ScoreQueue;
    std::queue<double> m_InGameTime;

    int m_FieldsSize = 0;
};
#endif //! SnakeGame_GameScenes_CSTATS_HPP