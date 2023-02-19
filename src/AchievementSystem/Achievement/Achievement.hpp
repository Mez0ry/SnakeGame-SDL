#ifndef SnakeGame_ACHIEVEMENT_HPP
#define SnakeGame_ACHIEVEMENT_HPP
#include "../../Texture/Texture.hpp"
#include "AchievementAnimation.hpp"
#include <memory>
#include <variant>

class Achievement {
private:
  template <typename _Type> 
  using ScopePtr = std::unique_ptr<_Type>;

public:
  Achievement() = default;
  ~Achievement() = default;

  void LoadTexture(const std::string &texture_path, int texture_width,int texture_height) {
    m_Texture.LoadTexture(texture_path);
    m_Texture.set_Rect<SourceRect>(0,0,texture_width,texture_height);
  }
  
  void set_dstRect(int x, int y, int w , int h){
    m_Texture.set_Rect(x,y,w,h);
  }
  
  void SetAchievementAlphaMod(uint8_t alpha){
    SDL_SetTextureAlphaMod(m_Texture.get_Texture(),alpha);
  }

  void AddAnimation(ScopePtr<AchievementAnimation> pAnim) {
    m_animation = std::move(pAnim);
  }

  void Update() {m_animation->Update(m_Texture.get_Rect()); }

  void Render() {m_Texture.RenderTexture(); }

  bool isUnlocked() const { return m_animation->isUnlocked(); }
  void set_isUnlocked(bool is_unlocked){ m_animation->set_isUnlocked(is_unlocked);}
private:
  Texture m_Texture;
  ScopePtr<AchievementAnimation> m_animation;
};
#endif //! SnakeGame_ACHIEVEMENT_HPP