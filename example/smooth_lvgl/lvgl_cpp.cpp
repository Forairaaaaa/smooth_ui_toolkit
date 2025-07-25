/**
 * @file lvgl_cpp.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/lvgl_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    auto screen = lv_screen_active();

    // Basic lvgl object
    auto obj = new Container(screen);
    obj->setPos(50, 50);
    obj->setSize(200, 100);

    // Label
    auto label = new Label(screen);
    label->setTextFont(&lv_font_montserrat_24);
    label->align(LV_ALIGN_CENTER, -180, 0);
    label->setText("??");

    // Button
    int count = 0;
    auto btn = new Button(screen);
    btn->setPos(50, 200);
    btn->label().setText("+1");
    btn->onClick().connect([&]() {
        label->setText(fmt::format("{}", count++));
    });

    // Switch
    auto sw = new Switch(screen);
    sw->setPos(50, 300);
    sw->onValueChanged().connect([&](bool value) {
        label->setText(value ? "ON" : "OFF");
    });

    // Slider
    auto slider = new Slider(screen);
    slider->setPos(50, 390);
    slider->onValueChanged().connect([&](int value) {
        label->setText(fmt::format("{}", value));
    });

    // Spinner
    auto spinner = new Spinner(screen);
    spinner->align(LV_ALIGN_CENTER, 0, -160);
    spinner->setArcWidth(3, LV_PART_MAIN);
    spinner->setArcWidth(3, LV_PART_INDICATOR);
    spinner->setSize(76, 76);

    // Roller
    auto roller = new Roller(screen);
    roller->align(LV_ALIGN_CENTER, 0, 0);
    roller->setOptions({"nihao", "wohao", "dajiahao"});
    roller->onValueChanged().connect([&](uint32_t value) {
        label->setText(fmt::format("{}", roller->getSelectedStr()));
    });

    // Chart
    auto chart = new Chart(screen);
    chart->align(LV_ALIGN_CENTER, 250, 0);
    chart->setSize(250, 200);
    chart->setPointCount(256);
    chart->setStyleSize(0, 0, LV_PART_INDICATOR);
    chart->setUpdateMode(LV_CHART_UPDATE_MODE_SHIFT);
    chart->setRange(LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);
    chart->addSeries(lv_color_hex(0x1e90ff), LV_CHART_AXIS_PRIMARY_Y);
    auto update_chart = [&]() {
        static uint32_t last_tick = 0;
        uint32_t tick = lv_tick_get();
        if (tick - last_tick > 10) {
            chart->setNextValue(0, sin(tick / 500.0) * 1000);
            last_tick = tick;
        }
    };

    while (1) {
        lvgl::update_window();
        update_chart();
    }

    return 0;
}
