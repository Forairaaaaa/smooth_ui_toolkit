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
#include "utils/lvgl_wrapper.h"
#include <animation/generators/spring/spring.h>
#include <animation/animate/animate.h>
#include <animation/animate_value/animate_value.h>
#include <animation/sequence/animate_value_sequence.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <utils/easing/ease.h>
#include <lvgl.h>
#include <thread>
#include <vector>

using namespace smooth_ui_toolkit;
using namespace mooncake;

struct Bubble {
    AnimateValue x;
    AnimateValue y;
    int radius;
    Color color;
};

int main()
{
    std::vector<Bubble> cursors;

    raylib::create_window(
        800, 450, "你好",
        [&]() {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                for (auto& cursor : cursors) {
                    cursor.x = GetMouseX();
                    cursor.y = GetMouseY();
                }
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                for (auto& cursor : cursors) {
                    cursor.x = GetRandomValue(0, GetScreenWidth());
                    cursor.y = GetRandomValue(0, GetScreenHeight());
                }
            }

            // Render
            ClearBackground(GetColor(0x181B1F));
            for (int i = 0; i < cursors.size(); i++) {
                DrawCircle(cursors[i].x, cursors[i].y, cursors[i].radius, cursors[i].color);
            }
        },
        [&]() {
            for (int i = 0; i < 1145; i++) {
                cursors.push_back({
                    (int)(GetScreenWidth() / 2),
                    (int)(GetScreenHeight() / 2),
                    GetRandomValue(3, 6),
                    GetRandomColor(),
                });
                cursors.back().x.springOptions().stiffness = GetRandomValue(50, 150);
                cursors.back().x.springOptions().damping = GetRandomValue(5, 15);
                cursors.back().y.springOptions() = cursors.back().x.springOptions();
                cursors.back().x = GetRandomValue(0, GetScreenWidth());
                cursors.back().y = GetRandomValue(0, GetScreenHeight());
            }
        });

    return 0;
}
