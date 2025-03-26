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
#include "number_flow/number_flow.h"
#include "utils/hal/hal.h"
#include "utils/lvgl_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>
#include <src/misc/lv_color.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    // {
    //     auto obj = new LvObject(lv_screen_active());
    //     // obj->setSize(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    //     // obj->setAlign(LV_ALIGN_CENTER);
    //     obj->setPos(0, 0);
    //     obj->setBgColor(lv_color_black());
    //     obj->setRotation(240);

    //     auto label = new LvLabel(lv_screen_active());
    //     label->setText("Hello");
    //     label->setAlign(LV_ALIGN_CENTER);
    //     label->setPos(0, 0);

    //     auto btn = new LvButton(lv_screen_active());
    //     btn->label().setText("asdasdasd");
    //     // btn->setAlign(LV_ALIGN_CENTER);
    //     btn->setPos(300, 100);

    //     auto sw = new LvSwitch();
    //     sw->create(lv_screen_active());
    //     sw->setPos(300, 200);

    //     // delete obj;
    //     // delete label;
    //     // delete btn;
    //     // delete sw;
    // }

    // auto digit = new DigitFlow(lv_screen_active());
    // digit->setAlign(LV_ALIGN_CENTER);
    // digit->setPos(0, 0);

    // // digit->init();
    // // delete digit;

    // int time_count = 0;
    // while (1) {
    //     if (ui_hal::get_tick() - time_count > 1000) {
    //         // digit->increase();
    //         digit->decrease();
    //         time_count = ui_hal::get_tick();
    //     }

    //     digit->update();
    //     lvgl::update_window();
    // }

    auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -110);
    number_flow->setTextFont(&lv_font_montserrat_48);

    auto flex_layout = new LvObject(lv_screen_active());
    flex_layout->setBorderWidth(0);
    flex_layout->setBgOpa(0);
    flex_layout->setFlexFlow(LV_FLEX_FLOW_ROW);
    flex_layout->setFlexAlign(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    flex_layout->setSize(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    flex_layout->setAlign(LV_ALIGN_CENTER);
    flex_layout->setPos(0, 150);
    flex_layout->setPadColumn(50);

    auto btn_next = new LvButton(flex_layout->get());
    btn_next->label().setText("-1");
    btn_next->onClick().connect([&]() { number_flow->setValue(number_flow->value() - 1); });

    auto btn_last = new LvButton(flex_layout->get());
    btn_last->label().setText("+1");
    btn_last->onClick().connect([&]() { number_flow->setValue(number_flow->value() + 1); });

    auto btn_random = new LvButton(flex_layout->get());
    btn_random->label().setText("random");
    btn_random->onClick().connect([&]() { number_flow->setValue(rand()); });

    int target_value = 0;
    auto slider = new LvSlider(flex_layout->get());
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
