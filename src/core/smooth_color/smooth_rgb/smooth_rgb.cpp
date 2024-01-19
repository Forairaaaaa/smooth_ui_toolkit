/**
 * @file smooth_rgb.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "smooth_rgb.h"

using namespace SmoothUIToolKit;

void SmoothRGB::start(const TimeSize_t& currentTime)
{
    _data.r_transition.start(currentTime);
    _data.g_transition.start(currentTime);
    _data.b_transition.start(currentTime);
}

void SmoothRGB::pause(const TimeSize_t& currentTime)
{
    _data.r_transition.pause(currentTime);
    _data.g_transition.pause(currentTime);
    _data.b_transition.pause(currentTime);
}

void SmoothRGB::end()
{
    _data.r_transition.end();
    _data.g_transition.end();
    _data.b_transition.end();
}

void SmoothRGB::reset()
{
    _data.r_transition.reset();
    _data.g_transition.reset();
    _data.b_transition.reset();
}

void SmoothRGB::update(const TimeSize_t& currentTime)
{
    if (_data.is_changed)
    {
        _data.is_changed = false;
        start(currentTime);
    }

    _data.r_transition.update(currentTime);
    _data.g_transition.update(currentTime);
    _data.b_transition.update(currentTime);

    // Invoke update callback
    if (_config.updateCallback != nullptr)
        _config.updateCallback(this);
}

void SmoothRGB::jumpTo(const int& red, const int& green, const int& blue)
{
    _data.r_transition.setConfig(_data.r_transition.getValue(), red);
    _data.g_transition.setConfig(_data.g_transition.getValue(), green);
    _data.b_transition.setConfig(_data.b_transition.getValue(), blue);
    end();
}

void SmoothRGB::moveTo(const int& red, const int& green, const int& blue)
{
    // If target not changed
    if (red == _data.r_transition.getEndValue() && green == _data.g_transition.getEndValue() &&
        blue == _data.b_transition.getEndValue())
        return;

    // Reset to new target
    _data.r_transition.setConfig(_data.r_transition.getValue(), red);
    _data.g_transition.setConfig(_data.g_transition.getValue(), green);
    _data.b_transition.setConfig(_data.b_transition.getValue(), blue);
    reset();

    // Tell update to start moving
    _data.is_changed = true;
}
