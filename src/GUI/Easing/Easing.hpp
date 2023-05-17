#ifndef __EASING_HPP__
#define __EASING_HPP__
#include <math.h>
#include <cstdint>

class Easing {
public:
  Easing() = default;
  ~Easing() = default;

  double easeInOutCubic(double progress) {
    return progress < 0.5 ? 4 * progress * progress * progress : 1 - pow(-2 * progress + 2, 3) / 2;
  }

  double easeOutQuint(double progress) { 
    return 1 - std::pow(1 - progress, 5); 
  }

  double easeInOutSine(double progress) {
    return -(std::cos(M_PI * progress) - 1) / 2;
  }
  
};
#endif // __EASING_HPP__