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
#include <functional>

using namespace mooncake;
using namespace smooth_ui_toolkit;

struct Position {
    AnimateValue x = 0;
    AnimateValue y = 0;
    AnimateValue rotate = 0;
};

class Box {
public:
    Box(int width, int height)
    {
        _lv_obj = lv_obj_create(lv_screen_active());
        lv_obj_center(_lv_obj);
        lv_obj_set_size(_lv_obj, width, height);
        lv_obj_set_style_transform_pivot_x(_lv_obj, width / 2, LV_PART_MAIN);
        lv_obj_set_style_transform_pivot_y(_lv_obj, height / 2, LV_PART_MAIN);
        lv_obj_set_style_radius(_lv_obj, (width + height) / 12, LV_PART_MAIN);
    }

    void move(const int& x, const int& y, const int& rotate)
    {
        lv_obj_set_x(_lv_obj, x);
        lv_obj_set_y(_lv_obj, y);
        lv_obj_set_style_transform_rotation(_lv_obj, rotate * 10, LV_PART_MAIN);
    }

private:
    lv_obj_t* _lv_obj;
};

class Slider {
public:
    Slider(const char* nameTag, int min, int max)
    {
        _lv_obj = lv_slider_create(lv_screen_active());
        lv_obj_center(_lv_obj);
        lv_slider_set_range(_lv_obj, min, max);
        lv_slider_set_value(_lv_obj, (max + min) / 2, LV_ANIM_ON);
        _label_name = lv_label_create(lv_screen_active());
        lv_label_set_text(_label_name, nameTag);
        _label_value = lv_label_create(lv_screen_active());
        lv_label_set_text_fmt(_label_value, "%d", lv_slider_get_value(_lv_obj));
    }

    void move(int x, int y)
    {
        lv_obj_set_x(_lv_obj, x);
        lv_obj_set_y(_lv_obj, y);
        lv_obj_align_to(_label_name, _lv_obj, LV_ALIGN_LEFT_MID, -80, 0);
        lv_obj_align_to(_label_value, _lv_obj, LV_ALIGN_RIGHT_MID, 50, 0);
    }

    void onValueChanged(std::function<void(int)> callback)
    {
        on_value_changed = callback;
        lv_obj_add_event_cb(
            _lv_obj,
            [](lv_event_t* e) {
                lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);
                auto value = (int)lv_slider_get_value(slider);
                auto this_class = (Slider*)lv_event_get_user_data(e);
                if (this_class->on_value_changed) {
                    this_class->on_value_changed(value);
                }
                lv_label_set_text_fmt(this_class->_label_value, "%d", value);
            },
            LV_EVENT_VALUE_CHANGED, this);
    }

    std::function<void(int)> on_value_changed;

private:
    lv_obj_t* _lv_obj;
    lv_obj_t* _label_name;
    lv_obj_t* _label_value;
};

int main()
{
    lvgl::create_window(800, 450);

    // Create a box on default position
    const int box_default_x = -230;
    const int box_default_y = 0;
    const int box_default_rotate = 0;
    Box box(250, 250);
    box.move(box_default_x, box_default_y, box_default_rotate);

    // Create box new postion buffer
    Position box_position = {box_default_x, box_default_y, box_default_rotate};

    // Create postion sliders
    Slider slider_x("x", -200, 200);
    slider_x.move(180, -100);
    slider_x.onValueChanged([&](int value) {
        box_position.x = box_default_x + value;
        mclog::info("move box x to {}", value);
    });

    Slider slider_y("y", -200, 200);
    slider_y.move(180, 0);
    slider_y.onValueChanged([&](int value) {
        box_position.y = box_default_y + value;
        mclog::info("move box y to {}", value);
    });

    Slider slider_rotate("rotate", -180, 180);
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
