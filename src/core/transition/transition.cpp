/**
 * @file transition.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "transition.h"

using namespace SmoothUIToolKit;

void Transition::start(const std::uint32_t& currentTime)
{
    // New time offset
    _data.time_offset = _data.time_offset + (currentTime - _data.pause_time) + _data.pause_offset;

    // Reset pause buffer
    _data.is_paused = false;
    _data.pause_offset = 0;
    _data.pause_time = 0;
}

void Transition::pause(const std::uint32_t& currentTime)
{
    _data.is_paused = true;
    _data.pause_offset = currentTime - _data.time_offset;
    _data.pause_time = currentTime;
}

void Transition::end()
{
    _data.is_paused = true;
    _data.is_finish = true;
    _data.current_value = _config.endValue;
}

void Transition::reset()
{
    _data.is_paused = true;
    _data.is_finish = false;
    _data.current_value = _config.startValue;
    _data.time_offset = 0;
}

void Transition::update(const std::uint32_t& currentTime)
{
    if (!_data.is_paused && !_data.is_finish)
    {
        auto delta_time = currentTime - _data.time_offset;

        // If still in delay
        if (delta_time < _config.delay)
        {
            _data.current_value = _config.startValue;
        }
        // If tranisiton finish
        else if ((delta_time - _config.delay) > _config.duration)
        {
            _data.current_value = _config.endValue;
            _data.is_finish = true;
        }
        else
        {
            _update_value(currentTime);
        }
    }

    // Invoke update callback
    if (_config.updateCallback != nullptr)
    {
        _config.updateCallback(this);
    }
}

void Transition::_update_value(const std::uint32_t& currentTime)
{
    std::uint32_t t_current = EasingPath::maxT * (currentTime - _config.delay - _data.time_offset) / _config.duration;
    _data.current_value =
        (_config.endValue - _config.startValue) * _config.transitionPath(t_current) / EasingPath::maxT + _config.startValue;
}
