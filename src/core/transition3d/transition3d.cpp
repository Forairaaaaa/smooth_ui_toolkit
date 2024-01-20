/**
 * @file transition3d.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "transition3d.h"

using namespace SmoothUIToolKit;

void Transition3D::start(const TimeSize_t& currentTime)
{
    _data.x_transition.start(currentTime);
    _data.y_transition.start(currentTime);
    _data.z_transition.start(currentTime);
}

void Transition3D::pause(const TimeSize_t& currentTime)
{
    _data.x_transition.pause(currentTime);
    _data.y_transition.pause(currentTime);
    _data.z_transition.pause(currentTime);
}

void Transition3D::end()
{
    _data.x_transition.end();
    _data.y_transition.end();
    _data.z_transition.end();
}

void Transition3D::reset()
{
    _data.x_transition.reset();
    _data.y_transition.reset();
    _data.z_transition.reset();
}

void Transition3D::update(const TimeSize_t& currentTime)
{
    if (_data.is_changed)
    {
        _data.is_changed = false;
        start(currentTime);
    }

    _data.x_transition.update(currentTime);
    _data.y_transition.update(currentTime);
    _data.z_transition.update(currentTime);

    // Invoke update callback
    if (_config.updateCallback != nullptr)
        _config.updateCallback(this);
}

void Transition3D::jumpTo(const int& x, const int& y, const int& z)
{
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    _data.z_transition.setConfig(_data.z_transition.getValue(), z);
    end();
}

void Transition3D::moveTo(const int& x, const int& y, const int& z)
{
    // If target not changed
    if (x == _data.x_transition.getEndValue() && y == _data.y_transition.getEndValue() && z == _data.z_transition.getEndValue())
        return;

    // Reset to new target
    _data.x_transition.setConfig(_data.x_transition.getValue(), x);
    _data.y_transition.setConfig(_data.y_transition.getValue(), y);
    _data.z_transition.setConfig(_data.z_transition.getValue(), z);
    reset();

    // Tell update to start moving
    _data.is_changed = true;
}
