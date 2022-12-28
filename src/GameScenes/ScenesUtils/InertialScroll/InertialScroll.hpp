#ifndef SCENES_UTILS_INERTIAL_SCROLL_HPP
#define SCENES_UTILS_INERTIAL_SCROLL_HPP
#include <cmath>
#include "SDL2/SDL.h"

typedef struct InertialScrollModel
{
    int scrolling;              // flag (scrolling or not)
    int scroll_sensitivity = 5; // how fast we want to scroll
    double scroll_y = 0;        // current scrolling amount (on Y-Axis)
    double scroll_acceleration; // scrolling speed
    double scroll_friction = 2; // how fast we decelerate

} InertialScrollModel;

class InertialScroll
{
public:
    InertialScroll();
    ~InertialScroll();
/**
 * @brief Decelerates scroll acceleration on each frame, until scroll acceleration there is less than 0.0005
*/
    void Decelerate();

/**
 * @brief Calculates acceleration
*/
    void CalculateAcceleration(bool isUp);

    const InertialScrollModel &get_Model() const { return m_Model; }

private:
    InertialScrollModel m_Model;
};
#endif //! SCENES_UTILS_INERTIAL_SCROLL_HPP