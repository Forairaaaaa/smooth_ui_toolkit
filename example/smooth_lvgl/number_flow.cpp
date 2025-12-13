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
#include "../utils/lvgl_wrapper.hpp"
#include <rajdhani/rajdhani_bold.h>
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>
#include <smooth_lvgl.hpp>
#include <mooncake_log.h>
#include <random>

using namespace uitk;
using namespace uitk::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -60);
    number_flow->setTextFont(&lv_font_rajdhani_bold_96);

    // 使用 easing 动画，效果会比 spring 差些
    // number_flow->animationType = AnimationType::Easing;

    // 透明背景
    // number_flow->transparentBg = false;

    // 显示正负号
    // number_flow->showPositiveSign = true;

    // 设置最小位数，不足时前导补0
    // number_flow->minDigits = 6;

    number_flow->init();

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
    btn_next->onClick().connect([&]() {
        number_flow->setValue(number_flow->value() - 1);
    });

    auto btn_last = new Button(flex_layout->get());
    btn_last->label().setText("+1");
    btn_last->onClick().connect([&]() {
        number_flow->setValue(number_flow->value() + 1);
    });

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
