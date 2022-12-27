#include "CMatchHistory.hpp"

CMatchHistory::CMatchHistory()
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "Other" + symbol + "buttons" + symbol + "return_button.png";

    // Return button
    m_ReturnButton.LoadTexture(texture_path.c_str());

    int width = CAppSettings::instance().get_WindowWidth() / 26;
    int height = CAppSettings::instance().get_WindowHeight() / 26;

    m_ReturnButton.set_dstRect(width, height, 72, 72);
    m_ReturnButton.set_srcRect(0, 0, 512, 512);

    // background texture
    int background_texture_resolutions[2][2] = {{1920, 1080}, {800, 800}};
    int row_index = ClosestTextureResolution<2, 2>(background_texture_resolutions, 2, 2);

    switch (row_index)
    {
    case 0:
    {
        texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "background_match_history_1920x1080.png";
        break;
    }
    case 1:
    {
        texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "background_match_history_800x800.png";
        break;
    }
    }

    m_BackgroundTexture.LoadTexture(texture_path.c_str());
    m_BackgroundTexture.set_dstRect(0, 0, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight());

    m_BackgroundTexture.set_srcRect(0, 0, background_texture_resolutions[row_index][0], background_texture_resolutions[row_index][1]);

    // Match board texture
    texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "match_board.png";
    m_MatchBoardTexture.LoadTexture(texture_path.c_str());

    int match_board_source_width = 583;
    int match_board_source_height = 333;

    m_MatchBoardTexture.set_srcRect(0, 0, match_board_source_width, match_board_source_height);

    int match_board_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.get_srcRect().w / 2);
    int match_board_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.get_srcRect().h / 2) + 40;

    m_MatchBoardTexture.set_dstRect(match_board_posX, match_board_posY, match_board_source_width, match_board_source_height);
}

CMatchHistory::~CMatchHistory()
{
}

void CMatchHistory::OnCreate()
{
    const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
    std::string file_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "score_history.cfg";

    std::ifstream istrm(file_path, std::ios::out);
    if (!istrm.is_open())
    {
        std::cerr << "Failed to open  'Score history' config file."
                  << " "
                  << "score history config path: " << file_path.c_str() << "\ncpp source filename: " << __FILENAME__;
    }

    std::string current_line;

    while (getline(istrm, current_line, ';'))
    {
        m_ScoreStack.push(std::stoi(current_line));
    }

    istrm.close();

    // Data fields
    std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "data_field.png";

    int data_field_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.get_srcRect().w / 2) + 5;
    int data_field_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.get_srcRect().h / 2) + 100;

    int data_field_source_width = 572;
    int data_field_source_height = 30;

    int space_between_data_fields = 15;

    if (m_DataFields == nullptr && !m_ScoreStack.empty())
    {
        m_DataFields = new DataField[m_ScoreStack.size()];
        m_FieldsSize = m_ScoreStack.size();
    }

    for (int i = 0; i < m_FieldsSize; i++)
    {
        m_DataFields[i].LoadTexture(texture_path);
        m_DataFields[i].set_Activity(true);

        m_DataFields[i].get_DataModel().score = m_ScoreStack.top();

        m_DataFields[i].get_Texture().set_dstRect(data_field_posX, data_field_posY + (i * (space_between_data_fields + data_field_source_height)), data_field_source_width, data_field_source_height);

        m_DataFields[i].get_Texture().set_srcRect(0, 0, data_field_source_width, data_field_source_height);

        m_ScoreStack.pop();
       
        m_DataFields[i].get_Range().top = data_field_posY - data_field_source_height;
        m_DataFields[i].get_Range().bottom = (data_field_posY + m_MatchBoardTexture.get_srcRect().h) - 110;
    }
}

void CMatchHistory::BeforeDestruction()
{
    
}

void CMatchHistory::OnDestroy()
{
    m_ReturnButton.DestroyTexture();

    m_ScoreStack = std::stack<int>();

    if (m_DataFields != nullptr && m_FieldsSize)
    {
        delete[] m_DataFields;
    }
    m_DataFields = nullptr;
    m_FieldsSize = 0;
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
            if (m_event.wheel.preciseY > 0)
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

            if (m_event.wheel.preciseY < 0)
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

    for (int i = 0; i < m_FieldsSize; i++)
    {
        m_DataFields[i].get_Texture().AdditionAssignmentToDstRect(0, m_InertialScrollModel.scroll_y, 0, 0);
        m_DataFields[i].Update();
    }
}

void CMatchHistory::Render()
{
    m_BackgroundTexture.DestroyTexture();
    m_BackgroundTexture.ReloadTexture();
    m_BackgroundTexture.RenderTexture();

    m_ReturnButton.DestroyTexture();
    m_ReturnButton.ReloadTexture();
    m_ReturnButton.RenderTexture();

    m_MatchBoardTexture.DestroyTexture();
    m_MatchBoardTexture.ReloadTexture();
    m_MatchBoardTexture.RenderTexture();

    for (int i = 0; i < 2; i++)
    {
        // if (m_InertialScrollModel.scroll_y > 0 && m_DataFieldTexture[i].get_dstRect().y + m_InertialScrollModel.scroll_y < m_range.bottom)
        // {
        //     m_DataFieldTexture[i].AdditionAssignmentToDstRect(0, m_InertialScrollModel.scroll_y, 0, 0);
        // }
        // else if (m_InertialScrollModel.scroll_y < 0 && m_DataFieldTexture[i].get_dstRect().y + m_InertialScrollModel.scroll_y > m_range.top)
        // {
        //     m_DataFieldTexture[i].AdditionAssignmentToDstRect(0, m_InertialScrollModel.scroll_y, 0, 0);
        // }
        // m_DataFieldTexture[i].AdditionAssignmentToDstRect(0, m_InertialScrollModel.scroll_y, 0, 0);
        // m_DataFieldTexture[i].DestroyTexture();
        // m_DataFieldTexture[i].ReloadTexture();
        // m_DataFieldTexture[i].RenderTexture();
    }
    for (int i = 0; i < m_FieldsSize; i++)
    {
        if (m_DataFields[i].isActive())
        {
            m_DataFields[i].Render();
        }
    }
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