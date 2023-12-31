/**
 * @file transition2d.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "transition2d.h"


using namespace SmoothUIToolKit;


void Transition2D::start(const std::uint32_t& currentTime)
{
    _data.x_transition.start(currentTime);
    _data.y_transition.start(currentTime);
}


void Transition2D::pause(const std::uint32_t& currentTime)
{
    _data.x_transition.pause(currentTime);
    _data.y_transition.pause(currentTime);
}


void Transition2D::end()
{
    _data.x_transition.end();
    _data.y_transition.end();
}


void Transition2D::reset()
{
    _data.x_transition.reset();
    _data.y_transition.reset();
}


void Transition2D::update(const std::uint32_t& currentTime)
{
    if (_data.is_changed)
    {
        _data.is_changed = false;
        start(currentTime);
    }

    _data.x_transition.update(currentTime);
    _data.y_transition.update(currentTime);

    // Invoke update callback 
    if (_config.updateCallback != nullptr)
        _config.updateCallback(this);
}


void Transition2D::jumpTo(const int& x, const int& y)
{
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    end();
}


void Transition2D::moveTo(const int& x, const int& y)
{
    // If target not changed 
    if (x == _data.x_transition.getEndValue() && y == _data.y_transition.getEndValue())
        return;

    // Reset to new target 
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    reset();

    // Tell update to start moving 
    _data.is_changed = true;
}
