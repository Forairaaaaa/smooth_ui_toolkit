/**
 * @file dev_zone.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2025-01-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <smooth_ui_toolkit.h>
#include <mooncake_log.h>
#include "../utils/raylib_wrapper.h"
#include "utils/hal/hal.h"
#include <animation/generators/spring/spring.h>
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    Spring anim;
    anim.animationOptions.start = 100;
    anim.animationOptions.end = 200;

    // raylib::create_window(800, 450, "你好👋", [&]() {
    //     ClearBackground(BLACK);
    //     DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    //     mclog::info("{}ms {:0.2f}s", ui_hal::get_tick_ms(), ui_hal::get_tick_s());
    // });
    return 0;
}
