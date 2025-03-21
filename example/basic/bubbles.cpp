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
    AnimateValue x;
    AnimateValue y;
    int radius;
    Color color;
};

int main()
{
    std::vector<Bubble> bubbles;

    raylib::create_window(
        800, 450, "你好",
        [&]() {
            // Move to mouse postion when click
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                for (auto& bubble : bubbles) {
                    bubble.x = GetMouseX();
                    bubble.y = GetMouseY();
                }
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                for (auto& bubble : bubbles) {
                    bubble.x = GetRandomValue(0, GetScreenWidth());
                    bubble.y = GetRandomValue(0, GetScreenHeight());
                }
            }

            // Render
            ClearBackground(BLACK);
            for (int i = 0; i < bubbles.size(); i++) {
                DrawCircle(bubbles[i].x, bubbles[i].y, bubbles[i].radius, bubbles[i].color);
            }
        },
        [&]() {
            // Generate random bubbles
            for (int i = 0; i < 1145; i++) {
                bubbles.push_back({
                    (int)(GetScreenWidth() / 2),
                    (int)(GetScreenHeight() / 2),
                    GetRandomValue(3, 6),
                    GetRandomColor(),
                });
                bubbles.back().x.springOptions().stiffness = GetRandomValue(50, 150);
                bubbles.back().x.springOptions().damping = GetRandomValue(5, 15);
                bubbles.back().y.springOptions() = bubbles.back().x.springOptions();
                bubbles.back().x = GetRandomValue(0, GetScreenWidth());
                bubbles.back().y = GetRandomValue(0, GetScreenHeight());
            }
        });

    return 0;
}
