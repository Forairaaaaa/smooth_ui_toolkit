/**
 * @file bubbles.cpp
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
#include <mooncake_log.h>
#include <vector>

using namespace smooth_ui_toolkit;

struct Bubble {
    AnimateVector2 pos;
    int radius;
    Color color;

    Bubble(int x_, int y_, int r, Color c) : pos(x_, y_), radius(r), color(c) {}
};

int main()
{
    std::vector<Bubble> bubbles;

    raylib::create_window(
        800,
        450,
        "你好",
        [&]() {
            // Move to mouse postion when click
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                for (auto& bubble : bubbles) {
                    bubble.pos.move(GetMouseX(), GetMouseY());
                }
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                for (auto& bubble : bubbles) {
                    bubble.pos.move(GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()));
                }
            }

            // Render
            ClearBackground(BLACK);
            for (int i = 0; i < bubbles.size(); i++) {
                DrawCircle(bubbles[i].pos.x, bubbles[i].pos.y, bubbles[i].radius, bubbles[i].color);
            }
        },
        [&]() {
            // Generate random bubbles
            for (int i = 0; i < 1145; i++) {
                bubbles.emplace_back(
                    (int)(GetScreenWidth() / 2), (int)(GetScreenHeight() / 2), GetRandomValue(3, 6), GetRandomColor());

                bubbles.back().pos.x.springOptions().stiffness = GetRandomValue(50, 150);
                bubbles.back().pos.x.springOptions().damping = GetRandomValue(5, 15);
                bubbles.back().pos.y.springOptions() = bubbles.back().pos.x.springOptions();
                bubbles.back().pos.move(GetRandomValue(0, GetScreenWidth()), GetRandomValue(0, GetScreenHeight()));
            }
        });

    return 0;
}
