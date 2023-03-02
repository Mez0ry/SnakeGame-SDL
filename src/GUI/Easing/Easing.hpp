#ifndef __EASING_HPP__
#define __EASING_HPP__
#include <cmath>
#include <cstdint>

class Easing {
public:
  Easing() = default;
  ~Easing() = default;

  double easeInOutCubic(double progress) {
    return progress < 0.5 ? 4 * progress * progress * progress : 1 - std::pow(-2 * progress + 2, 3) / 2;
  }

  double easeOutQuint(double progress) { 
    return 1 - std::pow(1 - progress, 5); 
  }

};
#endif // __EASING_HPP__