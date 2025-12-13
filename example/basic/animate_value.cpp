/**
 * @file animate_value.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;

int main()
{
    // Default value
    AnimateValue x = 100;
    AnimateValue y = 225;

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
