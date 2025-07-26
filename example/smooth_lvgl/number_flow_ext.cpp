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
#include "../utils/lvgl_wrapper.h"
#include <rajdhani/rajdhani_bold.h>
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>
#include <random>
#include <vector>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    auto get_random_prefix = []() {
        std::vector<std::string> prefix = {
            " ",
            "( ",
            "[ ",
            "{ ",
            "TEMP: ",
            "HUMI: ",
            "WEIGHT: ",
            "HEIGHT: ",
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, prefix.size() - 1);
        return prefix[dist(gen)];
    };

    auto get_random_suffix = []() {
        std::vector<std::string> suffix = {"", " )", " ]", " }", " C", " F", " K", " %", " $", " CM", " M", " KG"};
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, suffix.size() - 1);
        return suffix[dist(gen)];
    };

    auto get_random_value = []() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(-214748, 214748);
        return dist(gen);
    };

    auto number_flow = new NumberFlow(lv_screen_active());
    number_flow->setAlign(LV_ALIGN_CENTER);
    number_flow->setPos(0, -110);
    number_flow->setTextFont(&lv_font_rajdhani_bold_36);
    // number_flow->setTextColor(lv_color_hex(0x000000));

    // 单独设置前后缀颜色
    number_flow->prefixColor = "#00b894";
    number_flow->suffixColor = "#ff4757";

    auto btn_random = new Button(lv_screen_active());
    btn_random->align(LV_ALIGN_CENTER, 0, 100);
    btn_random->label().setText("random");
    btn_random->onClick().connect([&]() {
        number_flow->setPrefix(get_random_prefix());
        number_flow->setSuffix(get_random_suffix());
        number_flow->setValue(get_random_value());
    });

    while (1) {
        number_flow->update();
        lvgl::update_window();
    }

    return 0;
}
