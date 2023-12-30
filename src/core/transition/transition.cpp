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


void Transition::start(std::uint32_t currentTime)
{
    _data.time_offset = currentTime;
    _data.is_paused = false;
}


void Transition::pause()
{
    _data.is_paused = true;
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
}


void Transition::update(std::uint32_t currentTime)
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
        
        _update_value(currentTime);
    }

    // Invoke update callback
    _config.updateCallback(this);
}


void Transition::_update_value(const std::uint32_t& currentTime)
{
    std::uint32_t t_current = EasingPath::maxT / _config.duration * (currentTime - _config.delay);
    _data.current_value = (_config.endValue - _config.startValue) / EasingPath::maxT * _config.transitionPath(t_current);
}

