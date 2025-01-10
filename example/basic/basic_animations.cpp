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
#include "../utils/lvgl_wrapper.h"
#include <mooncake_log.h>
#include <smooth_ui_toolkit.h>
#include <animation/animate_value/animate_value.h>

using namespace mooncake;
using namespace smooth_ui_toolkit;

struct Position {
    AnimateValue x = 0;
    AnimateValue y = 0;
    AnimateValue rotate = 0;
};

int main()
{
    lvgl::create_window(800, 450);

    // Create a box
    lvgl::Box box(250, 250);

    // Set the box default position
    const int box_default_x = -230;
    const int box_default_y = 0;
    const int box_default_rotate = 0;

    // Create box postion buffer
    Position box_position = {box_default_x, box_default_y, box_default_rotate};

    // Create postion sliders
    lvgl::Slider slider_x("x", -200, 200);
    slider_x.move(180, -100);
    slider_x.onValueChanged([&](int value) {
        box_position.x = box_default_x + value;
        mclog::info("move box x to {}", value);
    });

    lvgl::Slider slider_y("y", -200, 200);
    slider_y.move(180, 0);
    slider_y.onValueChanged([&](int value) {
        box_position.y = box_default_y + value;
        mclog::info("move box y to {}", value);
    });

    lvgl::Slider slider_rotate("rotate", -180, 180);
    slider_rotate.move(180, 100);
    slider_rotate.onValueChanged([&](int value) {
        box_position.rotate = box_default_rotate + value;
        mclog::info("move box rotate to {}", value);
    });

    // Lvgl loop
    while (1) {
        // Keep moving the box to the new position
        box.move(box_position.x, box_position.y, box_position.rotate);
        lvgl::update_window();
    }

    return 0;
}
