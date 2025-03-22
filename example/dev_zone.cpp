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
#include "animation/animate_value/animate_value.h"
#include "lvgl/lvgl_cpp/obj.h"
#include "utils/raylib_wrapper.h"
#include "utils/lvgl_wrapper.h"
#include <lvgl/lvgl_cpp/label.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_scroll.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <lvgl/lvgl_cpp/button.h>
#include <vector>

using namespace smooth_ui_toolkit;
using namespace lvgl_cpp;

int main()
{
    lvgl::create_window(800, 520);

    std::vector<int> number_list = {9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    auto number_mask = new LvObject(lv_screen_active());

    number_mask->setTextFont(&lv_font_montserrat_24);
    number_mask->setTextFont(&lv_font_montserrat_48);

    number_mask->setPos(500, 100);
    number_mask->setPadding(0, 0, 0, 0);
    number_mask->setOutlineWidth(0);
    number_mask->setRadius(0);
    number_mask->setBorderWidth(0);

    auto font_height = lv_font_get_line_height(number_mask->getTextFont());
    mclog::info("font_height: {}", font_height);

    lv_obj_set_height(number_mask->get(), font_height);
    lv_obj_set_width(number_mask->get(), LV_SIZE_CONTENT);

    number_mask->removeFlag(LV_OBJ_FLAG_SCROLLABLE);
    number_mask->setBgOpa(LV_OPA_TRANSP);

    std::vector<LvLabel*> number_labels;
    for (int i = 0; i < number_list.size(); i++) {
        auto label = new LvLabel(number_mask->get());
        label->setText(std::to_string(number_list[i]));
        label->setAlign(LV_ALIGN_CENTER);
        number_labels.push_back(label);
    }

    int current_number_index = 1;
    AnimateValue y_offset = 0;
    y_offset.springOptions().visualDuration = 0.6;
    y_offset.springOptions().bounce = 0.2;
    y_offset = current_number_index * font_height;

    auto btn_next = new LvButton(lv_screen_active());
    btn_next->setPos(100, 100);
    btn_next->label().setText("next");
    btn_next->onClick().connect([&]() {
        if (current_number_index >= 10) {
            current_number_index = 1;
            y_offset.retarget(0 * font_height, 1 * font_height);
        } else {
            current_number_index++;
            y_offset = current_number_index * font_height;
        }
    });

    auto btn_last = new LvButton(lv_screen_active());
    btn_last->setPos(100, 200);
    btn_last->label().setText("last");
    btn_last->onClick().connect([&]() {
        if (current_number_index <= 1) {
            current_number_index = 10;
            y_offset.retarget(11 * font_height, 10 * font_height);
        } else {
            current_number_index--;
            y_offset = current_number_index * font_height;
        }
    });

    while (1) {

        for (int i = 0; i < number_labels.size(); i++) {
            number_labels[i]->setPos(0, i * font_height - y_offset);
        }

        // mclog::info("{} {}", current_number_index, y_offset.value());

        lvgl::update_window();
    }

    return 0;
}
