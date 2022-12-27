#ifndef SCENES_UTILS_INERTIAL_SCROLL_HPP
#define SCENES_UTILS_INERTIAL_SCROLL_HPP

typedef struct InertialScrollModel
{
    int scrolling;              // flag (scrolling or not)
    int scroll_sensitivity = 5; // how fast we want to scroll
    double scroll_y = 0;        // current scrolling amount (on Y-Axis)
    double scroll_acceleration; // scrolling speed
    double scroll_friction = 2; // how fast we decelerate
    double scroll_prev_pos;
} InertialScrollModel;

#endif //! SCENES_UTILS_INERTIAL_SCROLL_HPP