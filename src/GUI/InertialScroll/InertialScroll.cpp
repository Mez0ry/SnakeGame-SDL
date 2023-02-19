#include "InertialScroll.hpp"

InertialScroll::InertialScroll()
{
    
}

InertialScroll::~InertialScroll()
{

}

void InertialScroll::Decelerate()
{
    if (m_Model.scrolling)
    {
        if (m_Model.scroll_acceleration > 0)
            m_Model.scroll_acceleration -= m_Model.scroll_friction;

        if (m_Model.scroll_acceleration < 0)
            m_Model.scroll_acceleration += m_Model.scroll_friction;

        if (abs(m_Model.scroll_acceleration) < 0.0005)
            m_Model.scroll_acceleration = 0, m_Model.scrolling = false, m_Model.scroll_y = 0;

        m_Model.scroll_y += m_Model.scroll_sensitivity * m_Model.scroll_acceleration;
    }
}

void InertialScroll::CalculateAcceleration(double delta_y)
{

    if (m_Model.scrolling == 0)
    {
        m_Model.scrolling = 1;
    }
    else
    {
        m_Model.scroll_acceleration = delta_y * 30;
        m_Model.scrolling = 1;
    }
}
