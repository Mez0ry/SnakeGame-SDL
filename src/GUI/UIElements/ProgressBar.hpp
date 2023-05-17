#ifndef __PROGRESSBAR_HPP__
#define __PROGRESSBAR_HPP__
#include "../../Texture/Texture.hpp"
#include "../Easing/Easing.hpp"
#include <functional>
#include <math.h>
#include <stack>

class ProgressBar {
public:
  ProgressBar() : m_pEasingFunction(&Easing::easeInOutCubic), m_EaseOffset(0.016) {
    m_FgWidth = 0;
    m_TotalPercent = 0;
    m_EaseProgress = m_EaseOffset * 3;
  }

  void SetEasingMethod(std::function<double(Easing &, int)> ease_function) {
    this->m_pEasingFunction = ease_function;
  }

  void LoadBgTexture(const std::string &bg_path, const SDL_Rect &source_rect) {

    m_BgProgressTexture.LoadTexture(bg_path);
    m_BgProgressTexture.SetRect<SourceRect>({source_rect.x, source_rect.y}, TextureSize(source_rect.w, source_rect.h));
  }

  void LoadFgTexture(const std::string &fg_path, const SDL_Rect &source_rect) {
    m_FgProgressTexture.LoadTexture(fg_path);
    m_FgProgressTexture.SetRect<SourceRect>({source_rect.x, source_rect.y}, TextureSize(source_rect.w, source_rect.h));
  }

  void SetPosition(const Vec2 &position) {
    m_BgProgressTexture.SetTexturePosition(position);
    m_BgProgressTexture.SetRect({position.x, position.y}, TextureSize(m_BgProgressTexture.GetTextureSize().GetWidth(), m_BgProgressTexture.GetTextureSize().GetHeight()));
  }

  void SetSize(const TextureSize &size) {
   m_BgProgressTexture.SetTextureSize(size);
  }

  ~ProgressBar() {}

  void Update() {
    if (m_ProccessingPercent.empty())
      return;
    
    m_EaseProgress += m_EaseOffset;

    if (GetProgress() < m_ProccessingPercent.top()) {
      m_FgWidth += m_pEasingFunction(m_Easing, m_EaseProgress);
      m_FgProgressTexture.SetRect({m_BgProgressTexture.GetTexturePosition().x,m_BgProgressTexture.GetTexturePosition().y}, TextureSize(m_FgWidth, m_BgProgressTexture.GetTextureSize().GetHeight()));
    } else {
      m_ProccessingPercent.pop();
      m_EaseProgress = 0;
    }
    //m_FgProgressTexture.GetTexturePosition().x + m_FgProgressTexture.get_Rect().w  
    if (m_FgProgressTexture.top_right().x >= m_BgProgressTexture.top_right().x) {
      m_FgWidth = 0;
      m_FgProgressTexture.SetRect({m_BgProgressTexture.GetTexturePosition().x, m_BgProgressTexture.GetTexturePosition().y}, TextureSize(m_BgProgressTexture.GetTextureSize().GetWidth(), m_BgProgressTexture.GetTextureSize().GetHeight()));
    }
  }

  void Render() {
    m_BgProgressTexture.RenderTexture();
    m_FgProgressTexture.RenderTexture();
  }

  void Increase(const int percent) {
    m_TotalPercent += percent;
    m_ProccessingPercent.push((m_TotalPercent + percent <= m_Maximum) ? m_TotalPercent : 100);
  }

  /**
   * @return percent of how much progress bar filled at the moment
  */
  int GetProgress() {
    const SDL_Rect &fg_rect = m_FgProgressTexture.GetRect();
    const SDL_Rect &bg_rect = m_BgProgressTexture.GetRect();
    double filled_percent = 0;

    double bg_width = bg_rect.w, fg_width = fg_rect.w;
    double coefficient = bg_width / fg_width;

    filled_percent = (100 / coefficient);
    return (int)filled_percent;
  }

  bool isChanged() {
    if((GetProgress() != m_TotalPercent)){
      m_IsChanged = true;
      return m_IsChanged;
    }else{
      if(m_IsChanged){
        m_IsChanged = false;
        return true;
      }
      return false;
    }
  }

private:
  const int m_Maximum = 100;
  int m_TotalPercent;
  std::stack<int> m_ProccessingPercent;
  Texture m_BgProgressTexture;
  Texture m_FgProgressTexture;
  int m_FgWidth = 0;
  bool m_IsChanged = false;

  Easing m_Easing;
  double m_EaseProgress = 0;
  const double m_EaseOffset;
  std::function<double(Easing &, int)> m_pEasingFunction;
};

#endif // __PROGRESSBAR_HPP__