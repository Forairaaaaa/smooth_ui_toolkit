/**
 * @file hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "hal.h"

#ifdef SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL
#include <chrono>
#include <thread>
#endif

using namespace smooth_ui_toolkit;

#ifdef SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL
static std::chrono::steady_clock::time_point _start_time = std::chrono::steady_clock::now();
static uint32_t _default_get_tick()
{
    auto now = std::chrono::steady_clock::now();
    return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time).count());
}
#else
static uint32_t _default_get_tick()
{
    return 0; // Pass function when default HAL is disabled
}
#endif
static std::function<uint32_t(void)> _custom_get_tick;

void ui_hal::on_get_tick(std::function<uint32_t(void)> onGetTick)
{
    _custom_get_tick = onGetTick;
}

uint32_t ui_hal::get_tick()
{
    if (_custom_get_tick) {
        return _custom_get_tick();
    }
    return _default_get_tick();
}

float ui_hal::get_tick_s()
{
    auto ms = get_tick();
    if (ms == 0) {
        return 0;
    }
    return static_cast<float>(ms) / 1000.0f;
}

#ifdef SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL
static void _default_delay(uint32_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
#else
static void _default_delay(uint32_t ms)
{
    // Pass function when default HAL is disabled
    (void)ms; // Suppress unused parameter warning
}
#endif
static std::function<void(uint32_t)> _custom_delay;

void ui_hal::on_delay(std::function<void(uint32_t)> onDelay)
{
    _custom_delay = onDelay;
}

void ui_hal::delay(uint32_t ms)
{
    if (_custom_delay) {
        _custom_delay(ms);
        return;
    }
    _default_delay(ms);
}

void ui_hal::delay_s(float s)
{
    delay(static_cast<uint32_t>(s * 1000));
}
