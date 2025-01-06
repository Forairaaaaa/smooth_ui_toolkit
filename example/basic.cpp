/**
 * @file basic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <smooth_ui_toolkit.h>
#include "raylib_wrapper.h"
#include <animation/generators/spring/spring.h>
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;

int main()
{
    raylib::create_window(800, 450, "你好👋", []() {
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    });
    return 0;
}
