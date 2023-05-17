#include "CMatchHistory.hpp"

CMatchHistory::CMatchHistory() {
  m_DataFields.reserve(10);
  m_ScoreVec.reserve(10);
  m_InGameTimeVec.reserve(10);
  
  std::string data_field_texture = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/data_field.png");

  m_DataFieldTexture.LoadTexture(data_field_texture);
  
  std::string data_file_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/CMatchHistory-Data.cfg");

  auto clean_file = [&](const std::string &file_path) -> void {
    std::fstream fstr(file_path.c_str(),
                      std::ios::out | std::ios::in | std::ios::binary |
                          std::ios::trunc); // std::ios::trunc flag cleans file
    if (fstr.is_open())
      fstr.close();
  };

  clean_file(data_file_path.c_str());

  std::string texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/Other/buttons/return_button.png");
  
  // Return button
  m_ReturnButton.LoadTexture(texture_path.c_str());
  
  int pos_x = CAppSettings::instance().get_WindowWidth() / 26;
  int pos_y = CAppSettings::instance().get_WindowHeight() / 26;
  
  m_ReturnButton.SetRect({pos_x, pos_y}, TextureSize(52, 52));
  m_ReturnButton.SetRect<SourceRect>({0, 0}, TextureSize(512, 512));

  // background texture
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/background_match_history_800x800.png");

  m_BackgroundTexture.LoadTexture(texture_path.c_str());

  m_BackgroundTexture.SetRect<SourceRect>({0, 0}, TextureSize(800, 800));
  m_BackgroundTexture.SetRect({0, 0},TextureSize(CAppSettings::instance().get_WindowWidth(), CAppSettings::instance().get_WindowHeight()));

  // Match board texture
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/match_board.png");
  m_MatchBoardTexture.LoadTexture(texture_path.c_str());

  int match_board_source_width = 583;
  int match_board_source_height = 333;

  m_MatchBoardTexture.SetRect<SourceRect>({0, 0}, TextureSize(match_board_source_width, match_board_source_height));

  int match_board_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.GetTextureSize<SourceRect>().GetWidth() / 2);
  int match_board_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.GetTextureSize<SourceRect>().GetHeight() / 2) + 40;

  m_MatchBoardTexture.SetRect({match_board_posX, match_board_posY}, TextureSize(match_board_source_width, match_board_source_height));
  
  //ProgressBar
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/GUI/Recources/progress_bar/Background/bg_style1.png");
  m_ProgressBar.LoadBgTexture(texture_path,{0,0,235,9});
  texture_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/GUI/Recources/progress_bar/Foreground/fg_style1.png");
  m_ProgressBar.LoadFgTexture(texture_path,{0,0,235,9});

  TextureSize progress_bar_size(100,10);
  m_ProgressBar.SetSize(progress_bar_size);

  Vec2 progress_bar_pos;
  progress_bar_pos.x = (match_board_posX + (match_board_source_width / 2)) - progress_bar_size.GetWidth() / 2;
  progress_bar_pos.y = ((match_board_posY + match_board_source_height) + CAppSettings::instance().get_WindowHeight()) / 2;
  m_ProgressBar.SetPosition(progress_bar_pos);
  
  //ProgressPercentText
  std::string font_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/GUI/Recources/fonts/HACKED.ttf");
  m_ProgressText.LoadFont(font_path.c_str(),15);
  m_ProgressText->SetRect({(progress_bar_pos.x + progress_bar_size.GetWidth() - 35),progress_bar_pos.y + 15},TextureSize(15,10));
  m_ProgressText.LoadText(std::to_string(m_ProgressBar.GetProgress()).c_str(),{115, 124, 161,255});
  
  font_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/GUI/Recources/fonts/Comic_CAT.otf");
  m_PercentSymbolText.LoadFont(font_path.c_str(),15);
  m_PercentSymbolText->SetRect({m_ProgressText->GetTexturePosition().x + (m_ProgressText->GetTextureSize().GetWidth() + 5),m_ProgressText->GetTexturePosition().y},TextureSize(12,10));
  m_PercentSymbolText.LoadText("%",{115, 124, 161,255});
  
}

CMatchHistory::~CMatchHistory() {}

void CMatchHistory::OnCreate() {
  std::string file_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/assets/GameScenes/CMatchHistory/CMatchHistory-Data.cfg");

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

  //data fields

  int data_field_posX = (CAppSettings::instance().get_WindowWidth() / 2) - (m_MatchBoardTexture.GetTextureSize().GetWidth() / 2) + 5;
  int data_field_posY = (CAppSettings::instance().get_WindowHeight() / 2) - (m_MatchBoardTexture.GetTextureSize().GetHeight() / 2) + 100;

  const TextureSize df_size(572,30);
  
  int space_between_data_fields = 15;

  if (m_DataFields.size() < m_ScoreVec.size() && m_DataFields.size() < m_InGameTimeVec.size()) {
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
  
  if (m_DataFields.back().DataIsEmpty() && !m_DataFields.empty()) {
    auto& last_DataField = m_DataFields.back();
    last_DataField.ShareSDLTexture(m_DataFieldTexture);
    last_DataField.SetBgSize(df_size);
    
    last_DataField.SetSpaceBetweenText(115);
    last_DataField.AddContent(DataModel(std::to_string(m_DataFields.size()), 20, data_color));
    last_DataField.AddContent(DataModel(std::to_string(m_ScoreVec.back()), 20, data_color));

    std::string str = std::to_string(m_InGameTimeVec.back());

    // Deletes decimal part and leaves the fractional
    fnDelete_decimal_part(str);
    double seconds = std::stod(str) * 60;
    int minutes = (int)m_InGameTimeVec.back();
    std::string minutes_and_seconds = std::to_string(minutes) + " : " + std::to_string(seconds);
    last_DataField.AddContent(DataModel(minutes_and_seconds, 20, data_color, 50, 20));
  }
  
  for (int read_index = m_DataFields.size() - 1, offset = 0; read_index >= 0 && !m_DataFields.empty(); read_index--,offset++) {
    Vec2 datafield_rect_pos;
    datafield_rect_pos.x = data_field_posX;
    datafield_rect_pos.y = data_field_posY + (offset * (space_between_data_fields + df_size.GetHeight()));


    m_DataFields[read_index].SetBgPosition(datafield_rect_pos);
    m_DataFields[read_index].SetBgPosition<SourceRect>({0,0});

    m_DataFields[read_index].SetBgSize(df_size);
  }

  m_ProgressBar.Increase(5);
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
      if (m_event.button.button == SDL_BUTTON_LEFT && m_ReturnButton.PointIsOnTexture(cursor_pos)) {
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

void CMatchHistory::Update(float dt) {
  m_InertialScroll.Decelerate();
  m_ProgressBar.Update();
  for (int i = 0; i < m_DataFields.size(); i++) {
    Vec2 new_pos;
    new_pos.x = m_DataFields[i].GetBgPosition().x;
    new_pos.y = m_DataFields[i].GetBgPosition().y + m_InertialScroll.get_Model().scroll_y;

    m_DataFields[i].SetBgPosition(new_pos); 
    m_DataFields[i].Update();
  }
}

void CMatchHistory::Render() {
  m_BackgroundTexture.RenderTexture();
  m_ReturnButton.RenderTexture();
  m_MatchBoardTexture.RenderTexture();

  m_ProgressBar.Render();

  m_PercentSymbolText.RenderText();
  if(m_ProgressBar.isChanged()){
    m_ProgressText.Reset();
    m_ProgressText.LoadText(std::to_string(m_ProgressBar.GetProgress()).c_str(),{115, 124, 161,255});
  }
  m_ProgressText.RenderText();
  
  SDL_Rect clip_rect = {m_MatchBoardTexture.GetTexturePosition().x, m_MatchBoardTexture.GetTexturePosition().y + 40, m_MatchBoardTexture.GetTextureSize().GetWidth(), (m_MatchBoardTexture.GetTexturePosition().y + m_MatchBoardTexture.GetTextureSize().GetHeight()) - 10};

  SDL_RenderSetClipRect(CSDLContext::instance().get_renderer(), &clip_rect);

  for (int i = 0; i < m_DataFields.size(); i++) {
    if ((m_DataFields[i].GetBgPosition().y + 36) < (m_MatchBoardTexture.GetTexturePosition().y + m_MatchBoardTexture.GetTextureSize<SourceRect>().GetHeight()) - 5) {
      m_DataFields[i].Render();
    }
  }

  SDL_RenderSetClipRect(CSDLContext::instance().get_renderer(), NULL);
}