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
public:
  Datafield() : m_SpaceBetweenText(0){}
  Datafield(const std::string &background_texture_path, int width, int height){
    LoadBackgroundTexture(background_texture_path, width, height);
  }

  void LoadBackgroundTexture(const std::string &background_texture_path, int width, int height) {
    m_BackgroundTexture.LoadTexture(background_texture_path);
    m_BackgroundTexture.SetRect<SourceRect>({0, 0}, TextureSize(width, height));
    
    m_BackgroundTexture.SetRect({0, 0}, TextureSize(width, height));
  }
  
  void ShareSDLTexture(const Texture& texture){
    m_BackgroundTexture.ShareSDLTexture(texture);
  }

  void AddContent(const DataModel &data,const std::string& font_path = "") {
    m_Data.push_back(data);
 
    const std::string default_font_path = CAppSettings::instance().get_SourceFolder() + CAppSettings::GetCorrectedPath("/GUI/Recources/fonts/HACKED.ttf");
    
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

  template <typename _Type = DestRect>
  void SetBgPosition(const Vec2& pos){
    m_BackgroundTexture.SetTexturePosition<_Type>(pos);
  }

  void SetBgSize(const TextureSize& size){
      m_BackgroundTexture.SetTextureSize<SourceRect>(size);
      m_BackgroundTexture.SetTextureSize(size);
  }

  template <typename _Type = DestRect>
  Vec2 GetBgPosition() const {
    return m_BackgroundTexture.GetTexturePosition<_Type>();
  }

  template <typename _Type = DestRect>
  TextureSize GetBgSize() const {
    return m_BackgroundTexture.GetTextureSize<_Type>();
  }
  
  void SetSpaceBetweenText(int space_between_text) {
    m_SpaceBetweenText = space_between_text;
  }

  void Update() {
    int space_between_text = 0;
    for (int read_index = 0; read_index < m_TextVec.size() && read_index < m_Data.size();read_index++,space_between_text += m_SpaceBetweenText) {
      auto& curr_text = m_TextVec[read_index];

      TextureSize text_size(m_Data[read_index].dataWidth_, m_Data[read_index].dataHeight_);

      curr_text->SetRect({(m_BackgroundTexture.GetTexturePosition().x + m_Data[read_index].dataSize_) + space_between_text, (m_BackgroundTexture.GetTexturePosition().y + m_BackgroundTexture.GetTextureSize().GetHeight() / 2) - curr_text->GetTextureSize().GetHeight() / 2}, text_size);
      curr_text->SetRect<SourceRect>({0,0},TextureSize(m_Data[read_index].dataWidth_ * 2, m_Data[read_index].dataHeight_ * 2));
    }
  }

  void Render() {
    m_BackgroundTexture.RenderTexture();
    for (auto &text : m_TextVec) {
      text.RenderText();
    }
  }

private:
  std::vector<DataModel> m_Data;
  Texture m_BackgroundTexture;
  std::vector<Text> m_TextVec;
  int m_SpaceBetweenText;
};
#endif // __DATAFIELD_HPP__