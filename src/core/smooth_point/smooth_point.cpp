/**
 * @file smooth_point.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "smooth_point.h"


using namespace SmoothUIToolKit;


void SmoothPoint::start(const std::uint32_t& currentTime)
{
    _data.x_transition.start(currentTime);
    _data.y_transition.start(currentTime);
}


void SmoothPoint::pause()
{
    _data.x_transition.pause();
    _data.y_transition.pause();
}


void SmoothPoint::end()
{
    _data.x_transition.end();
    _data.y_transition.end();
}


void SmoothPoint::reset()
{
    _data.x_transition.reset();
    _data.y_transition.reset();
}


void SmoothPoint::update(const std::uint32_t& currentTime)
{
    _data.x_transition.update(currentTime);
    _data.y_transition.update(currentTime);

    // Invoke update callback 
    if (_config.updateCallback != nullptr)
        _config.updateCallback(this);
}


void SmoothPoint::jumpTo(const int& x, const int& y)
{
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    end();
}


void SmoothPoint::moveTo(const int& x, const int& y, const std::uint32_t& currentTime)
{
    // Reset to new target 
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    reset();
    start(currentTime);
}
