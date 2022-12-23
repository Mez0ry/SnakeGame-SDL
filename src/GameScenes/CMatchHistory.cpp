#include "CMatchHistory.hpp"

CMatchHistory::CMatchHistory()
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "Other" + symbol + "buttons" + symbol + "return_button.png";
    m_ReturnButton.LoadTexture(texture_path.c_str());

    int width = CAppSettings::instance().get_WindowWidth() / 26;
    int height = CAppSettings::instance().get_WindowHeight() / 26;

    m_ReturnButton.set_dstRect(width, height, 72, 72);
    m_ReturnButton.set_srcRect(0, 0, 512, 512);

    int background_texture_resolutions[2][2] = {{1920, 1080}, {800, 800}};
    int row_index = ClosestTextureResolution<2, 2>(background_texture_resolutions, 2, 2);

    switch(row_index){
        case 0:{
            texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "background_match_history_1920x1080.png";
            break;
        }
        case 1:{
            texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "background_match_history_800x800.png";
            break;
        }
    }

    m_BackgroundTexture.LoadTexture(texture_path.c_str());
    m_BackgroundTexture.set_dstRect(0, 0, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight());

    m_BackgroundTexture.set_srcRect(0, 0, background_texture_resolutions[row_index][0], background_texture_resolutions[row_index][1]);

    texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "data_field.png";
    m_DataFieldTexture.LoadTexture(texture_path.c_str());

    m_DataFieldTexture.set_dstRect(CAppSettings::instance().get_WindowWidth() / 2 - 50, (CAppSettings::instance().get_WindowHeight() / 2) - 10, 300, 125);

    int data_field_source_width = 520;
    int data_field_source_height = 172;
    
    m_DataFieldTexture.set_srcRect(0, 0, 520, 172);
}

CMatchHistory::~CMatchHistory()
{
}

void CMatchHistory::OnCreate()
{
}

void CMatchHistory::BeforeDestruction()
{
}

void CMatchHistory::OnDestroy()
{
    m_ReturnButton.DestroyTexture();
}

void CMatchHistory::InputHandler()
{
    while (SDL_PollEvent(&m_event) != 0)
    {
        CursorPosition cursor_pos;
        cursor_pos.x = m_event.motion.x;
        cursor_pos.y = m_event.motion.y;
        switch (m_event.type)
        {
        case SDL_QUIT:
        {

            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            if (m_event.button.button == SDL_BUTTON_LEFT && m_ReturnButton.CursorIsColliding(cursor_pos))
            {
                g_GameSceneType = GameSceneType::Menu;
            }

            break;
        } // case: !SDL_MOUSEBUTTONDOWN

        case SDL_MOUSEWHEEL:
        {
            if (m_event.wheel.preciseY < 0)
            {
                if (m_InertialScrollModel.scrolling == 0)
                {
                    m_InertialScrollModel.scrolling = 1;
                    m_InertialScrollModel.scroll_prev_pos = m_event.wheel.y;
                }
                else
                {
                    double dy = (m_event.wheel.y - m_InertialScrollModel.scroll_prev_pos) + 0.2;
                    m_InertialScrollModel.scroll_acceleration = dy * 30;
                    m_InertialScrollModel.scroll_prev_pos = m_event.wheel.y;
                    m_InertialScrollModel.scrolling = 1;
                }
            }

            if (m_event.wheel.preciseY > 0)
            {
                if (m_InertialScrollModel.scrolling == 0)
                {
                    m_InertialScrollModel.scrolling = 1;
                    m_InertialScrollModel.scroll_prev_pos = m_event.wheel.y;
                }
                else
                {
                    double dy = (m_event.wheel.y - m_InertialScrollModel.scroll_prev_pos) - 0.2;
                    m_InertialScrollModel.scroll_acceleration = dy * 30;
                    m_InertialScrollModel.scroll_prev_pos = m_event.wheel.y;
                    m_InertialScrollModel.scrolling = 1;
                }
            }
        }

        case SDL_MOUSEMOTION:
        {

            break;
        } // case: !SDL_MOUSEMOTION
        } // !switch

    } //! SDL_PollEvent
}

void CMatchHistory::Update()
{
    if (m_InertialScrollModel.scrolling)
    {
        if (m_InertialScrollModel.scroll_acceleration > 0)
            m_InertialScrollModel.scroll_acceleration -= m_InertialScrollModel.scroll_friction;

        if (m_InertialScrollModel.scroll_acceleration < 0)
            m_InertialScrollModel.scroll_acceleration += m_InertialScrollModel.scroll_friction;

        if (abs(m_InertialScrollModel.scroll_acceleration) < 0.0005)
            m_InertialScrollModel.scroll_acceleration = 0;
        m_InertialScrollModel.scroll_y += m_InertialScrollModel.scroll_sensitivity * m_InertialScrollModel.scroll_acceleration;
    }

    if (abs(m_InertialScrollModel.scroll_acceleration) < 0.0005)
        m_InertialScrollModel.scroll_acceleration = 0, m_InertialScrollModel.scrolling = false, m_InertialScrollModel.scroll_y = 0;

}

void CMatchHistory::Render()
{
    m_BackgroundTexture.DestroyTexture();
    m_BackgroundTexture.ReloadTexture();
    m_BackgroundTexture.RenderTexture();

    m_ReturnButton.DestroyTexture();
    m_ReturnButton.ReloadTexture();
    m_ReturnButton.RenderTexture();

    m_DataFieldTexture.AdditionAssignmentToDstRect(0, m_InertialScrollModel.scroll_y, 0, 0);

    m_DataFieldTexture.DestroyTexture();
    m_DataFieldTexture.ReloadTexture();
    m_DataFieldTexture.RenderTexture();
}

template <typename std::size_t Row_Size, typename std::size_t Col_Size>
constexpr int CMatchHistory::ClosestTextureResolution(int texture_resolution_arr[Row_Size][Col_Size], int row, int col)
{
    int window_width = CAppSettings::instance().get_WindowWidth();
    int window_height = CAppSettings::instance().get_WindowHeight();

    int closest_width = INT_MAX;
    int closest_height = INT_MAX;

    int index = -1;

    for (int i = 0; i < row; i++)
    {
        for (int j = 1; j < col; j++)
        {
            int width_diff = texture_resolution_arr[i][j - 1] - window_width;
            int height_diff = texture_resolution_arr[i][j] - window_height;

            if (abs(width_diff) < closest_width)
            {
                index = i;
                closest_width = abs(width_diff);
            }

            if (abs(height_diff) < closest_height)
            {
                index = i;
                closest_height = abs(height_diff);
            }
        }
    }

    return index;
}