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
#include "utils/raylib_wrapper.h"
#include "raylib.h"
#include "utils/hal/hal.h"
#include <animation/generators/spring/spring.h>
#include <animation/animate/animate.h>
#include <animation/animate_value/animate_value.h>
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    // Spring anim;
    // anim.start = 50;
    // anim.end = 600;

    // anim.springOptions.duration = 1000;
    // anim.springOptions.bounce = 0.3;
    // anim.springOptions.visualDuration = 0.8;

    AnimateValue anim_val;
    anim_val = 100;
    mclog::info("{}", (float)anim_val);

    anim_val = 600;
    mclog::info("{}", (float)anim_val);

    anim_val.begin();
    mclog::info("{}", (float)anim_val);

    anim_val = 100;
    mclog::info("{}", (float)anim_val);

    raylib::create_window(800, 450, "你好👋", [&]() {
        ClearBackground(BLACK);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawCircle(anim_val, 225, 30, LIGHTGRAY);

        // mclog::info("mouse {} {} {}", GetMouseX(), GetMouseY(), IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mclog::info("{}", GetMouseX());
            anim_val = GetMouseX();
        }
    });

    return 0;
}
