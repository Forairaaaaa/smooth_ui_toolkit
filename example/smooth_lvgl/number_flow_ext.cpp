/**
 * @file number_flow_ext.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-07-26
 *
 * @copyright Copyright (c) 2025
 *
 */
// Refs: https://number-flow.barvian.me
#include "../utils/lvgl_wrapper.hpp"
#include <rajdhani/rajdhani_bold.h>
#include <smooth_ui_toolkit.hpp>
#include <smooth_lvgl.hpp>
#include <mooncake_log.h>
#include <random>
#include <vector>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

NumberFlow* prefix_suffix_and_color()
{
    static auto get_random_prefix = []() {
        std::vector<std::string> prefix = {
            " ",
            "( ",
            "[ ",
            "{ ",
            "Temp: ",
            "Humi: ",
            "Weight: ",
            "Height: ",
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, prefix.size() - 1);
        return prefix[dist(gen)];
    };

    static auto get_random_suffix = []() {
        std::vector<std::string> suffix = {
            "", " )", " ]", " }", " C", " F", " K", " %", " $", " cm", " m", " kg", " mm"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, suffix.size() - 1);
        return suffix[dist(gen)];
    };

    static auto get_random_value = []() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-214748, 214748);
        return dist(gen);
    };

    static auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -123);
    number_flow->setTextFont(&lv_font_rajdhani_bold_72);

    // 设置初始前后缀（要在 init 之前）
    number_flow->setPrefix("( ");
    number_flow->setSuffix(" )");

    number_flow->init();

    // 设置颜色 (要在 init 之后)
    number_flow->setPrefixColor(lv_color_hex(0x00b894));
    number_flow->setDigitColor(lv_color_hex(0xa29bfe));
    number_flow->setSuffixColor(lv_color_hex(0xff4757));

    number_flow->addFlag(LV_OBJ_FLAG_CLICKABLE);
    number_flow->onClick().connect([&]() {
        number_flow->setPrefix(get_random_prefix());
        number_flow->setSuffix(get_random_suffix());
        number_flow->setValue(get_random_value());
    });

    return number_flow;
}

NumberFlowFloat* number_flow_float()
{
    static auto number_flow = new NumberFlowFloat(lv_screen_active());
    number_flow->align(LV_ALIGN_CENTER, 0, 50);
    number_flow->setTextFont(&lv_font_rajdhani_bold_64);

    // 设置小数位数
    number_flow->setDecimalPlaces(2);

    number_flow->setSuffix(" Kg");

    number_flow->init();

    number_flow->setDigitColor(lv_color_hex(0xf6e58d));
    number_flow->setSuffixColor(lv_color_hex(0xdff9fb));

    auto btn_random = new Button(lv_screen_active());
    btn_random->align(LV_ALIGN_CENTER, -200, 150);
    btn_random->label().setText("Random");
    btn_random->onClick().connect([&]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-99999.99f, 99999.99f);
        float randomValue = dist(gen);
        number_flow->setValue(randomValue);
    });

    auto btn_increment = new Button(lv_screen_active());
    btn_increment->align(LV_ALIGN_CENTER, 0, 150);
    btn_increment->label().setText("+0.01");
    btn_increment->onClick().connect([&]() {
        number_flow->setValue(number_flow->value() + 0.01f);
    });

    auto btn_decrement = new Button(lv_screen_active());
    btn_decrement->align(LV_ALIGN_CENTER, 200, 150);
    btn_decrement->label().setText("-0.01");
    btn_decrement->onClick().connect([&]() {
        number_flow->setValue(number_flow->value() - 0.01f);
    });

    return number_flow;
}

int main()
{
    lvgl::create_window(800, 520);

    // 前后缀文本、颜色
    auto num_1 = prefix_suffix_and_color();

    // 小数支持
    auto num_2 = number_flow_float();

    while (1) {
        num_1->update();
        num_2->update();
        lvgl::update_window();
    }

    return 0;
}
