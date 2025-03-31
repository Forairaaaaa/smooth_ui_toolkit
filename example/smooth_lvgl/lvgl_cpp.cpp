/**
 * @file number_flow.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#include "../utils/lvgl_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    // Basic lvgl object
    auto obj = new Container(lv_screen_active());
    obj->setPos(50, 50);
    obj->setSize(200, 100);

    // Label
    auto label = new Label(lv_screen_active());
    label->setTextFont(&lv_font_montserrat_24);
    label->setAlign(LV_ALIGN_CENTER);
    label->setText("????????????");

    // Button
    int count = 0;
    auto btn = new Button(lv_screen_active());
    btn->setPos(50, 200);
    btn->label().setText("+1");
    btn->onClick().connect([&]() { label->setText(fmt::format("{}", count++)); });

    // Switch
    auto sw = new Switch(lv_screen_active());
    sw->setPos(50, 300);
    sw->onValueChanged().connect([&](bool value) { label->setText(value ? "ON" : "OFF"); });

    // Slider
    auto slider = new Slider(lv_screen_active());
    slider->setPos(50, 400);
    slider->onValueChanged().connect([&](int value) { label->setText(fmt::format("{}", value)); });

    while (1) {
        lvgl::update_window();
    }

    return 0;
}
