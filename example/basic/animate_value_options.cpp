/**
 * @file animate_value_options.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <animation/animate_value/animate_value.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;

int main()
{
    // Default value
    AnimateValue x = 100;
    AnimateValue y = 225;

    // Stop animation before option setting
    x.stop();
    y.stop();

    x.springOptions().bounce = 0.1;
    y.springOptions().bounce = 0.1;
    x.springOptions().visualDuration = 0.6;
    y.springOptions().visualDuration = 0.6;

    // Begin animation
    x.begin();
    y.begin();

    raylib::create_window(800, 450, "你好", [&]() {
        // Update new position on mouse click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mclog::info("new postion ({}, {})", GetMouseX(), GetMouseY());
            x = GetMouseX();
            y = GetMouseY();
        }

        // Render
        ClearBackground(BLACK);
        DrawText("Click To Move The Ball", 280, 200, 20, DARKGRAY);
        DrawCircle(x, y, 30, LIGHTGRAY);
    });

    return 0;
}
