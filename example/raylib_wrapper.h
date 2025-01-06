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

inline void create_window(int width, int height, const char* title, std::function<void()> onDraw)
{
    InitWindow(width, height, title);

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