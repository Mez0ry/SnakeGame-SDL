#ifndef SnakeGame_ACHIEVEMENT_BASE_HPP
#define SnakeGame_ACHIEVEMENT_BASE_HPP
#include "../CAppSettings/CAppSettings.hpp"
#include "../TextureManager/TextureManager.hpp"

template <typename Derived>
class Achievement {
 public:
  Derived *get_DerivedInstance() { return static_cast<Derived *>(this); }

  void Update() { get_DerivedInstance()->Update(); }
  void Render() { get_DerivedInstance()->Render(); }
  void set_IsUnlocking(bool status) { get_DerivedInstance()->set_IsUnlocking(status); }
  bool get_IsUnlocking() { return get_DerivedInstance()->get_IsUnlocking(); }
  bool IsUnlocked() { return get_DerivedInstance()->IsUnlocked(); }
  void set_IsUnlocked(bool isUnlockedStatus) { get_DerivedInstance()->set_IsUnlocked(isUnlockedStatus);  }

 private:
  Achievement() = default;
  friend Derived;
};
#endif  //! SnakeGame_ACHIEVEMENT_BASE_HPP
// mixin callback