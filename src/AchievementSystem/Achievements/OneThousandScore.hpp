#ifndef SnakeGame_ACHIEVEMENTS_ONE_THOUSAND_SCORE_HPP
#define SnakeGame_ACHIEVEMENTS_ONE_THOUSAND_SCORE_HPP
#include <vector>
#include "../Achievement.hpp"
class OneThousandScore : public Achievement<OneThousandScore> {
 public:
  OneThousandScore();
  ~OneThousandScore();

  void Update();
  void Render();
  void set_IsUnlocking(bool status) { m_isUnlocking = status; }
  bool get_IsUnlocking() { return m_isUnlocking; }
  bool IsUnlocked() { return m_isUnlocked; }
  void set_IsUnlocked(bool isUnlockedStatus){this->m_isUnlocked = isUnlockedStatus;}
 private:
  bool m_isUnlocked = false;
  bool m_isUnlocking = false;
  TextureManager m_AchievementTexture;
  SDL_Rect m_PositionChanger;
  std::vector<bool> m_AnimationStages;
};
#endif  //! SnakeGame_ACHIEVEMENTS_ONE_THOUSAND_SCORE_HPP