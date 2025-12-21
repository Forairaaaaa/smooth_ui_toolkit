/**
 * @file frame_clock.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-12-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "core/hal/hal.hpp"

namespace smooth_ui_toolkit::games {

class FrameClock {
public:
    void tick()
    {
        _current = ui_hal::get_tick_s();
        _dt = _current - _last;
        _last = _current;
    }

    float dt() const
    {
        return _dt;
    }
    float now() const
    {
        return _current;
    }

private:
    float _current = 0.0f;
    float _last = 0.0f;
    float _dt = 0.0f;
};

} // namespace smooth_ui_toolkit::games
