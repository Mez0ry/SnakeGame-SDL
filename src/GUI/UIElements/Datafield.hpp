#ifndef __DATAFIELD_HPP__
#define __DATAFIELD_HPP__
#include "../../Texture/Texture.hpp"
#include "../../Vector.hpp"
#include "../Text/Text.hpp"
#include "../base.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include "../../CAppSettings/CAppSettings.hpp"

struct DataModel {
  DataModel() = default;
  DataModel(const std::string &data,int text_size,SDL_Color data_color,int data_width = 20,int data_height = 20) : sData_(data),dataSize_(text_size), dataColor_(data_color) , dataWidth_(data_width), dataHeight_(data_height){}
  std::string sData_;
  SDL_Color dataColor_;
  int dataSize_;
  int dataWidth_,dataHeight_;

  template <typename T> T GetAs() {
    static_assert("No specialization for this kind of type");
  }
};

template <> inline int DataModel::GetAs<int>() { return std::stoi(sData_); }

template <> inline bool DataModel::GetAs<bool>() {
  return (std::stoi(sData_) == 1) ? true : false;
}

template <> inline float DataModel::GetAs<float>() {
  return std::stof(sData_);
}

template <> inline double DataModel::GetAs<double>() {
  return std::stod(sData_);
}

class Datafield {
private:
  using DataModelVecType = std::vector<DataModel>;
  using TextVecType = std::vector<Text>;

public:
  Datafield() : m_SpaceBetweenText(0){}
  Datafield(const std::string &background_texture_path, int width, int height){
    LoadBackgroundTexture(background_texture_path, width, height);
  }

  void LoadBackgroundTexture(const std::string &background_texture_path, int width, int height) {
    m_BackgroundTexture.LoadTexture(background_texture_path);
    m_BackgroundTexture.set_Rect<SourceRect>(0, 0, width, height);
    m_BackgroundTexture.set_Rect(0, 0, width, height);
  }
  
  void SetBackgroundTexture(SDL_Texture* texture){
    m_BackgroundTexture.set_Texture(texture);
  }

  void AddContent(const DataModel &data,const std::string& font_path = "") {
    m_Data.push_back(data);
    const std::string& symbol_ref = CAppSettings::instance().get_SlashSymbol();
    const std::string default_font_path = CAppSettings::instance().get_SourceFolder() + symbol_ref + "GUI" + symbol_ref + "Recources" + symbol_ref + "fonts" + symbol_ref + "HACKED.ttf";
    
    std::string final_font_path = (font_path.empty()) ? default_font_path : font_path;
    m_TextVec.push_back(Text(final_font_path.c_str(), data.dataSize_, data.sData_.c_str(), data.dataColor_));
  }

  void RemoveContent(unsigned int index) {
    m_TextVec.erase(m_TextVec.begin() + index);
  }

  const DataModel &GetData(unsigned int index) {
    return m_Data[index];
  }
  
  bool DataIsEmpty() const {return m_Data.empty();}

  void SetBackgroundPosition(const Vec2 &position) {
    m_BackgroundTexture.set_Rect(position.x, position.y,m_BackgroundTexture.get_Rect().w, m_BackgroundTexture.get_Rect().h);
  }

  void SetBackgroundSize(const Vec2 &size) {
    m_BackgroundTexture.set_Rect(m_BackgroundTexture.get_Rect().x, m_BackgroundTexture.get_Rect().y, size.x,size.y);
  }

  SDL_Rect& GetBackgroundRect(){
    return m_BackgroundTexture.get_Rect();
  }

  void SetSpaceBetweenText(int space_between_text) {
    m_SpaceBetweenText = space_between_text;
  }

  void Update() {
    int space_between_text = 0;
    for (int read_index = 0; read_index < m_TextVec.size() && read_index < m_Data.size();read_index++,space_between_text += m_SpaceBetweenText) {
      auto& curr_text = m_TextVec[read_index];
  
      curr_text.set_Rect((m_BackgroundTexture.get_Rect().x + m_Data[read_index].dataSize_) + space_between_text, (m_BackgroundTexture.get_Rect().y + m_BackgroundTexture.get_Rect().h / 2) - curr_text.get_Rect().h / 2, m_Data[read_index].dataWidth_, m_Data[read_index].dataHeight_);
    }
  }

  void Render() {
    m_BackgroundTexture.RenderTexture();
    for (auto &text : m_TextVec) {
      text.RenderText();
    }
  }

private:
  DataModelVecType m_Data;
  Texture m_BackgroundTexture;
  TextVecType m_TextVec;
  int m_SpaceBetweenText;
};
#endif // __DATAFIELD_HPP__