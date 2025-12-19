/**
 * @file hal.hpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <cstdint>
#include <functional>
// https://wiki.libsdl.org/SDL2/SDL_GetTicks
// https://wiki.libsdl.org/SDL2/SDL_Delay

namespace smooth_ui_toolkit {
namespace ui_hal {

void on_get_tick(std::function<uint32_t(void)> onGetTick);
void on_delay(std::function<void(uint32_t)> onDelay);

/**
 * @brief Get the number of milliseconds since running
 *
 * @return uint32_t
 */
uint32_t get_tick();

/**
 * @brief Get the number of seconds since running
 *
 * @return float
 */
float get_tick_s();

/**
 * @brief Wait a specified number of milliseconds before returning
 *
 * @param ms
 */
void delay(uint32_t ms);

/**
 * @brief Wait a specified number of seconds before returning
 *
 * @param s
 */
void delay_s(float s);

} // namespace ui_hal
} // namespace smooth_ui_toolkit
