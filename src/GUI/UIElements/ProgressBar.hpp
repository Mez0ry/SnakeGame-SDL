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
    m_BgProgressTexture.set_Rect<SourceRect>(source_rect.x, source_rect.y, source_rect.w, source_rect.h);
  }

  void LoadFgTexture(const std::string &fg_path, const SDL_Rect &source_rect) {
    m_FgProgressTexture.LoadTexture(fg_path);
    m_FgProgressTexture.set_Rect<SourceRect>(source_rect.x, source_rect.y, source_rect.w, source_rect.h);
  }

  void SetPosition(const Vec2 &position) {
    m_BgProgressTexture.set_Rect(position.x, position.y, m_BgProgressTexture.get_Rect().w, m_BgProgressTexture.get_Rect().h);
  }

  void SetSize(const Vec2 &size) {
    m_BgProgressTexture.set_Rect(m_BgProgressTexture.get_Rect().x, m_BgProgressTexture.get_Rect().y, size.x, size.y);
  }

  ~ProgressBar() {}

  void Update() {
    if (m_ProccessingPercent.empty())
      return;
    
    m_EaseProgress += m_EaseOffset;

    if (GetProgress() < m_ProccessingPercent.top()) {
      m_FgWidth += m_pEasingFunction(m_Easing, m_EaseProgress);
      m_FgProgressTexture.set_Rect(m_BgProgressTexture.get_Rect().x,m_BgProgressTexture.get_Rect().y, m_FgWidth, m_BgProgressTexture.get_Rect().h);
    } else {
      m_ProccessingPercent.pop();
      m_EaseProgress = 0;
    }

    if (m_FgProgressTexture.get_Rect().x + m_FgProgressTexture.get_Rect().w >= m_BgProgressTexture.get_Rect().x + m_BgProgressTexture.get_Rect().w) {
      m_FgWidth = 0;
      m_FgProgressTexture.set_Rect(m_BgProgressTexture.get_Rect().x, m_BgProgressTexture.get_Rect().y, m_BgProgressTexture.get_Rect().w, m_BgProgressTexture.get_Rect().h);
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
    const SDL_Rect &fg_rect = m_FgProgressTexture.get_Rect();
    const SDL_Rect &bg_rect = m_BgProgressTexture.get_Rect();
    double filled_percent = 0;

    double bg_width = bg_rect.w, fg_width = fg_rect.w;
    double coefficient = bg_width / fg_width;

    filled_percent = (100 / coefficient);
    return (int)filled_percent;
  }

private:
  const int m_Maximum = 100;
  int m_TotalPercent;
  std::stack<int> m_ProccessingPercent;
  Texture m_BgProgressTexture;
  Texture m_FgProgressTexture;
  int m_FgWidth = 0;

  Easing m_Easing;
  double m_EaseProgress = 0;
  const double m_EaseOffset;
  std::function<double(Easing &, int)> m_pEasingFunction;
};

#endif // __PROGRESSBAR_HPP__