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
#include "lvgl_cpp/button.h"
#include "lvgl_cpp/obj.h"
#include "lvgl_cpp/slider.h"
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>
#include <random>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -110);
    number_flow->setTextFont(&lv_font_montserrat_48);
    // number_flow->transparentBg = false;
    // number_flow->showPositiveSign = true;

    auto flex_layout = new Container(lv_screen_active());
    flex_layout->setBorderWidth(0);
    flex_layout->setBgOpa(0);
    flex_layout->setFlexFlow(LV_FLEX_FLOW_ROW);
    flex_layout->setFlexAlign(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    flex_layout->setSize(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    flex_layout->setAlign(LV_ALIGN_CENTER);
    flex_layout->setPos(0, 150);
    flex_layout->setPadColumn(50);

    auto btn_next = new Button(flex_layout->get());
    btn_next->label().setText("-1");
    btn_next->onClick().connect([&]() { number_flow->setValue(number_flow->value() - 1); });

    auto btn_last = new Button(flex_layout->get());
    btn_last->label().setText("+1");
    btn_last->onClick().connect([&]() { number_flow->setValue(number_flow->value() + 1); });

    auto btn_random = new Button(flex_layout->get());
    btn_random->label().setText("random");
    btn_random->onClick().connect([&]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-2147483648, 2147483647);
        int randomNum = dist(gen);
        number_flow->setValue(randomNum);
    });

    int target_value = 0;
    auto slider = new Slider(flex_layout->get());
    slider->setRange(1, 9);
    slider->setValue(1);
    slider->onValueChanged().connect([&](int value) {
        int target_value = 0;
        for (int i = 1; i <= value; ++i) {
            target_value = target_value * 10 + i;
        }
        number_flow->setValue(target_value);
    });

    while (1) {
        number_flow->update();
        lvgl::update_window();
    }

    return 0;
}
