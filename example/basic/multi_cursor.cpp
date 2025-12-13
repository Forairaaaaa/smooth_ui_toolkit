/**
 * @file multi_cursor.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-10
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://motion.dev/docs/react-animation bottom Motion+: "Introducing Cursor"
#include "../utils/raylib_wrapper.hpp"
#include <mooncake_log.h>
#include <smooth_ui_toolkit.hpp>
#include <vector>

using namespace smooth_ui_toolkit;

struct MyVector2D {
    AnimateValue x;
    AnimateValue y;
};

void update_cursors(int mouseX, int mouseY, std::vector<MyVector2D>& cursors)
{
    const int radius = 55;
    const float angleStep = 60.0f;
    for (int i = 0; i < 6; ++i) {
        float angle = angleStep * i * (M_PI / 180.0f);
        int dx = static_cast<int>(radius * cos(angle));
        int dy = static_cast<int>(radius * sin(angle));
        cursors[i].x = mouseX + dx;
        cursors[i].y = mouseY + dy;
    }
}

int main()
{
    // Create cursors
    std::vector<MyVector2D> cursors(6);
    // Create cursor colors
    std::vector<long> colors = {0xFF0088FF, 0xDD00EEFF, 0x9911FFFF, 0x7700FFFF, 0x4400FFFF, 0x0D63F8FF};

    // Setup cursors animation options
    for (int i = 0; i < cursors.size(); i++) {
        cursors[i].x.stop();
        cursors[i].y.stop();
        cursors[i].x.springOptions().stiffness = 55 + i * 25;
        cursors[i].x.springOptions().damping = 13 - i;
        cursors[i].y.springOptions() = cursors[i].x.springOptions();
        cursors[i].x.begin();
        cursors[i].y.begin();
    }

    raylib::create_window(
        800,
        450,
        "你好",
        [&]() {
            // If mouse inside of window, move to mouse position
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){0, 0, 800, 450})) {
                update_cursors(GetMouseX(), GetMouseY(), cursors);
            }
            // If not, move back to center
            else {
                update_cursors(GetScreenWidth() / 2, GetScreenHeight() / 2, cursors);
            }

            // Render
            ClearBackground(BLACK);
            DrawCircle(GetMouseX(), GetMouseY(), 8, WHITE);
            for (int i = 0; i < cursors.size(); i++) {
                DrawCircle(cursors[i].x, cursors[i].y, 8, GetColor(colors[i]));
            }
        },
        []() {
            HideCursor();
        });

    return 0;
}
