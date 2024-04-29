/**
 * @file transition4d.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "transition4d.h"

using namespace SmoothUIToolKit;

void Transition4D::start(const TimeSize_t& currentTime)
{
    _data.x_transition.start(currentTime);
    _data.y_transition.start(currentTime);
    _data.w_transition.start(currentTime);
    _data.h_transition.start(currentTime);
}

void Transition4D::pause(const TimeSize_t& currentTime)
{
    _data.x_transition.pause(currentTime);
    _data.y_transition.pause(currentTime);
    _data.w_transition.pause(currentTime);
    _data.h_transition.pause(currentTime);
}

void Transition4D::end()
{
    _data.x_transition.end();
    _data.y_transition.end();
    _data.w_transition.end();
    _data.h_transition.end();
}

void Transition4D::reset()
{
    _data.x_transition.reset();
    _data.y_transition.reset();
    _data.w_transition.reset();
    _data.h_transition.reset();
}

void Transition4D::update(const TimeSize_t& currentTime)
{
    if (_data.is_changed)
    {
        _data.is_changed = false;
        start(currentTime);
    }

    _data.x_transition.update(currentTime);
    _data.y_transition.update(currentTime);
    _data.w_transition.update(currentTime);
    _data.h_transition.update(currentTime);

    // Invoke update callback
    if (_config.updateCallback != nullptr)
        _config.updateCallback(this);
}

void Transition4D::jumpTo(const int& x, const int& y, const int& w, const int& h)
{
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    _data.w_transition.setConfig(_data.w_transition.getValue(), w);
    _data.h_transition.setConfig(_data.h_transition.getValue(), h);
    end();
}

void Transition4D::moveTo(const int& x, const int& y, const int& w, const int& h)
{
    // If target not changed
    if (x == _data.x_transition.getEndValue() && y == _data.y_transition.getEndValue() &&
        w == _data.w_transition.getEndValue() && h == _data.h_transition.getEndValue())
        return;

    // Reset to new target
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    _data.w_transition.setConfig(_data.w_transition.getValue(), w);
    _data.h_transition.setConfig(_data.h_transition.getValue(), h);
    reset();

    // Tell update to start moving
    _data.is_changed = true;
}
