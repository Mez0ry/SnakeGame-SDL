#include "CMatchHistory.hpp"

CMatchHistory::CMatchHistory() {
  m_DataFields.reserve(10);
  m_ScoreVec.reserve(10);
  m_InGameTimeVec.reserve(10);

  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string data_file_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "CMatchHistory-Data.cfg";

  auto clean_file = [&](const std::string &file_path) -> void {
    std::fstream fstr(file_path.c_str(),
                      std::ios::out | std::ios::in | std::ios::binary |
                          std::ios::trunc); // std::ios::trunc flag cleans file
    if (fstr.is_open())
      fstr.close();
  };

  clean_file(data_file_path.c_str());

  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "Other" + symbol + "buttons" + symbol + "return_button.png";

  // Return button
  m_ReturnButton.LoadTexture(texture_path.c_str());
  
  int width = CAppSettings::instance().get_WindowWidth() / 26;
  int height = CAppSettings::instance().get_WindowHeight() / 26;

  m_ReturnButton.set_Rect(width, height, 52, 52);
  m_ReturnButton.set_Rect<SourceRect>(0, 0, 512, 512);

  // background texture
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" +  symbol + "background_match_history_800x800.png";

  m_BackgroundTexture.LoadTexture(texture_path.c_str());

  m_BackgroundTexture.set_Rect<SourceRect>(0, 0, 800, 800);
  m_BackgroundTexture.set_Rect(0, 0, CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight());

  // Match board texture
  texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "match_board.png";
  m_MatchBoardTexture.LoadTexture(texture_path.c_str());

  int match_board_source_width = 583;
  int match_board_source_height = 333;

  m_MatchBoardTexture.set_Rect<SourceRect>(0, 0, match_board_source_width, match_board_source_height);

  int match_board_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.get_Rect<SourceRect>().w / 2);
  int match_board_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.get_Rect<SourceRect>().h / 2) + 40;

  m_MatchBoardTexture.set_Rect(match_board_posX, match_board_posY, match_board_source_width, match_board_source_height);
}

CMatchHistory::~CMatchHistory() {}

void CMatchHistory::OnCreate() {
  const std::string &symbol = CAppSettings::instance().get_SlashSymbol();
  std::string file_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "CMatchHistory-Data.cfg";

  Serializer des;
  if (Serializer::Deserialize(des, file_path)) {
    auto &node = des["CMatchHistory-Data"];
    auto &time_property = node["Time"];
    auto &score_property = node["Score"];

    const int new_added_elem_index = 0;
    if (time_property.get_DataSize() > m_InGameTimeVec.size() && score_property.get_DataSize() > m_ScoreVec.size()) {
      m_InGameTimeVec.push_back(time_property.GetAs<double>(new_added_elem_index));
      m_ScoreVec.push_back(score_property.GetAs<int>(new_added_elem_index));
    }
  }

  // Data fields
  std::string texture_path = CAppSettings::instance().get_SourceFolder() + symbol + "assets" + symbol + "GameScenes" + symbol + "CMatchHistory" + symbol + "data_field.png";

  int data_field_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.get_Rect<SourceRect>().w / 2) + 5;
  int data_field_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.get_Rect<SourceRect>().h / 2) + 100;

  int data_field_source_width = 572;
  int data_field_source_height = 30;

  int space_between_data_fields = 15;

  if (m_DataFields.size() < m_ScoreVec.size() &&
      m_DataFields.size() < m_InGameTimeVec.size()) {
    m_DataFields.resize(m_DataFields.size() + 1);
  }

  auto fnDelete_decimal_part = [&](std::string &str_out) {
    for (int i = 0; i < str_out.length(); i++) {
      if (str_out[i] == ',' || str_out[i] == '.') {
        return;
      }
      str_out[i] = '0';
    }
  };

  SDL_Color data_color = {100, 165, 204, 255};

  if (m_DataFields.back().DataIsEmpty()) {

    m_DataFields.back().LoadBackgroundTexture(
        texture_path, data_field_source_width, data_field_source_height);
    m_DataFields.back().SetSpaceBetweenText(115);
    m_DataFields.back().AddContent(DataModel(std::to_string(m_DataFields.size()), 20, data_color));
    m_DataFields.back().AddContent(DataModel(std::to_string(m_ScoreVec[m_ScoreVec.size() - 1]), 20, data_color));

    std::string str = std::to_string(m_InGameTimeVec[m_InGameTimeVec.size() - 1]);

    // Deletes decimal part and leaves the fractional
    fnDelete_decimal_part(str);
    double seconds = std::stod(str) * 60;
    int minutes = (int)m_InGameTimeVec[m_InGameTimeVec.size() - 1];
    std::string minutes_and_seconds = std::to_string(minutes) + " : " + std::to_string(seconds);
    m_DataFields.back().AddContent(DataModel(minutes_and_seconds, 20, data_color, 50, 20));
  }
  
  for (int i = 0; i < m_DataFields.size(); i++) {
    Vec2 datafield_rect_pos;
    datafield_rect_pos.x = data_field_posX;
    datafield_rect_pos.y = data_field_posY + (i * (space_between_data_fields + data_field_source_height));

    Vec2 datafield_rect_size;
    datafield_rect_size.x = data_field_source_width;
    datafield_rect_size.y = data_field_source_height;

    m_DataFields[m_DataFields.size() - i - 1].SetBackgroundPosition(datafield_rect_pos);
    m_DataFields[m_DataFields.size() - i - 1].SetBackgroundSize(datafield_rect_size);
  }
}

void CMatchHistory::OnDestroy() {}

void CMatchHistory::InputHandler() {
  while (SDL_PollEvent(&m_event) != 0) {
    Vec2 cursor_pos;
    cursor_pos.x = m_event.motion.x;
    cursor_pos.y = m_event.motion.y;
    switch (m_event.type) {
    case SDL_QUIT: {

      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      if (m_event.button.button == SDL_BUTTON_LEFT && m_ReturnButton.CursorIsColliding(cursor_pos)) {
        g_GameSceneType = GameSceneType::Menu;
      }

      break;
    } // case: !SDL_MOUSEBUTTONDOWN

    case SDL_MOUSEWHEEL: {
      if (m_event.wheel.preciseY > 0) {
        m_InertialScroll.CalculateAcceleration(0.2);
      }

      if (m_event.wheel.preciseY < 0) {
        m_InertialScroll.CalculateAcceleration(-0.2);
      }
    }

    case SDL_MOUSEMOTION: {

      break;
    } // case: !SDL_MOUSEMOTION
    } // !switch

  } //! SDL_PollEvent
}

void CMatchHistory::Update() {
  m_InertialScroll.Decelerate();

  for (int i = 0; i < m_DataFields.size(); i++) {
    m_DataFields[i].GetBackgroundRect().y += m_InertialScroll.get_Model().scroll_y;
    m_DataFields[i].Update();
  }
}

void CMatchHistory::Render() {
  m_BackgroundTexture.RenderTexture();
  m_ReturnButton.RenderTexture();
  m_MatchBoardTexture.RenderTexture();

  SDL_Rect clip_rect = {m_MatchBoardTexture.get_Rect().x, m_MatchBoardTexture.get_Rect().y + 40, m_MatchBoardTexture.get_Rect().w, (m_MatchBoardTexture.get_Rect().y + m_MatchBoardTexture.get_Rect().h) - 10};

  SDL_RenderSetClipRect(CSDLContext::instance().get_renderer(), &clip_rect);

  for (int i = 0; i < m_DataFields.size(); i++) {
    if ((m_DataFields[i].GetBackgroundRect().y + 36) < (m_MatchBoardTexture.get_Rect().y + m_MatchBoardTexture.get_Rect<SourceRect>().h) - 5) {
      m_DataFields[i].Render();
    }
  }

  SDL_RenderSetClipRect(CSDLContext::instance().get_renderer(), NULL);
}