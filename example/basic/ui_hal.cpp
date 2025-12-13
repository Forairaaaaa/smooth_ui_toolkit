/**
 * @file ui_hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>
#include <mooncake_log.h>

using namespace uitk;

int main()
{
    // Custom on tick callback
    // ui_hal::on_get_tick_ms([]() {
    //     return millis();
    //     return SDL_GetTicks();
    // });

    // Custom on delay callback
    // ui_hal::on_delay([](uint32_t ms) {
    //     delay(ms);
    //     SDL_Delay(ms);
    // });

    while (1) {
        mclog::info("{}ms {}s", ui_hal::get_tick(), ui_hal::get_tick_s());
        ui_hal::delay(500);
        mclog::info("{}ms {}s", ui_hal::get_tick(), ui_hal::get_tick_s());
        ui_hal::delay_s(0.5);
    }
    return 0;
}
