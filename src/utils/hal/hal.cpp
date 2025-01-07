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
#include <chrono>
#include <thread>

using namespace smooth_ui_toolkit;

static std::chrono::steady_clock::time_point _start_time = std::chrono::steady_clock::now();
static uint32_t _default_on_get_tick()
{
    auto now = std::chrono::steady_clock::now();
    return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now - _start_time).count());
}
static std::function<uint32_t(void)> _on_get_tick = _default_on_get_tick;

void ui_hal::on_get_tick(std::function<uint32_t(void)> onGetTick)
{
    _on_get_tick = onGetTick;
}

uint32_t ui_hal::get_tick()
{
    return _on_get_tick();
}

float ui_hal::get_tick_s()
{
    auto ms = get_tick();
    if (ms == 0) {
        return 0;
    }
    return static_cast<float>(ms) / 1000.0f;
}

static void _default_on_delay(uint32_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
static std::function<void(uint32_t)> _on_delay = _default_on_delay;

void ui_hal::on_delay(std::function<void(uint32_t)> onDelay)
{
    _on_delay = onDelay;
}

void ui_hal::delay(uint32_t ms)
{
    _on_delay(ms);
}

void ui_hal::delay_s(float s)
{
    delay(static_cast<uint32_t>(s * 1000));
}
