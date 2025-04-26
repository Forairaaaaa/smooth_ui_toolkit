/**
 * @file raylib_wrapper.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#pragma once
#include <functional>
#include <raylib.h>

namespace raylib {

inline void create_window(int width,
                          int height,
                          const char* title,
                          std::function<void()> onDraw,
                          std::function<void()> onSetup = nullptr)
{
    InitWindow(width, height, title);

    if (onSetup) {
        onSetup();
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        if (onDraw) {
            onDraw();
        }
        EndDrawing();
    }

    CloseWindow();
}

} // namespace raylib

inline Color GetRandomColor()
{
    Color ret;
    ret.r = GetRandomValue(0, 255);
    ret.g = GetRandomValue(0, 255);
    ret.b = GetRandomValue(0, 255);
    ret.a = GetRandomValue(10, 255);
    return ret;
}
