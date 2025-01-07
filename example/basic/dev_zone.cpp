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
#include "raylib.h"
#include "utils/hal/hal.h"
#include <animation/generators/spring/spring.h>
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    Spring anim;
    anim.animationOptions.start = 50;
    anim.animationOptions.end = 600;

    anim.springOptions.duration = 1000;
    anim.springOptions.bounce = 0.3;
    anim.springOptions.visualDuration = 0.8;

    raylib::create_window(800, 450, "你好👋", [&]() {
        ClearBackground(BLACK);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        auto value = anim.next(ui_hal::get_tick_s()).value;
        mclog::info("{}", value);

        DrawCircle(value, 225, 30, LIGHTGRAY);
    });

    return 0;
}
