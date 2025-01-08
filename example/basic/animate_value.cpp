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
#include "../utils/raylib_wrapper.h"
#include "raylib.h"
#include <smooth_ui_toolkit.h>
#include <animation/animate_value/animate_value.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    AnimateValue anim_x;
    AnimateValue anim_y;

    // Default value
    anim_x = 100;
    anim_y = 225;

    // Begin value animation
    anim_x.begin();
    anim_y.begin();

    raylib::create_window(800, 450, "你好👋", [&]() {
        ClearBackground(BLACK);
        DrawText("Click To Move The Ball", 280, 200, 20, DARKGRAY);
        DrawCircle(anim_x, anim_y, 30, LIGHTGRAY);

        // Update new position when click
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            mclog::info("new postion ({}, {})", GetMouseX(), GetMouseY());
            anim_x = GetMouseX();
            anim_y = GetMouseY();
        }
    });

    return 0;
}
