/**
 * @file lvgl_wrapper.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <functional>
#include <thread>
#include <lvgl.h>

namespace lvgl {

void create_window(int width, int height)
{
    lv_init();

    lv_group_set_default(lv_group_create());

    auto display = lv_sdl_window_create(width, height);
    lv_display_set_default(display);

    auto mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, display);

    auto mouse_wheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mouse_wheel, display);
    lv_indev_set_group(mouse_wheel, lv_group_get_default());

    auto keyboard = lv_sdl_keyboard_create();
    lv_indev_set_display(keyboard, display);
    lv_indev_set_group(keyboard, lv_group_get_default());

    lv_obj_set_scroll_dir(lv_screen_active(), LV_DIR_NONE);
}

void update_window()
{
    lv_timer_handler();
}

class Box {
public:
    Box(int width, int height)
    {
        _box = lv_obj_create(lv_screen_active());
        lv_obj_center(_box);
        lv_obj_set_size(_box, width, height);
        lv_obj_set_style_transform_pivot_x(_box, width / 2, LV_PART_MAIN);
        lv_obj_set_style_transform_pivot_y(_box, height / 2, LV_PART_MAIN);
        lv_obj_set_style_radius(_box, (width + height) / 12, LV_PART_MAIN);
    }

    void move(const int& x, const int& y, const int& rotate)
    {
        lv_obj_set_x(_box, x);
        lv_obj_set_y(_box, y);
        lv_obj_set_style_transform_rotation(_box, rotate * 10, LV_PART_MAIN);
    }

private:
    lv_obj_t* _box;
};

class Slider {
public:
    Slider(const char* nameTag = "", int min = 0, int max = 100)
    {
        _slider = lv_slider_create(lv_screen_active());
        lv_obj_center(_slider);
        range(min, max);
        _name_label = lv_label_create(lv_screen_active());
        this->nameTag(nameTag);
        _value_label = lv_label_create(lv_screen_active());
        lv_label_set_text_fmt(_value_label, "%d", lv_slider_get_value(_slider));
    }

    void nameTag(const char* nameTag)
    {
        lv_label_set_text(_name_label, nameTag);
    }

    void range(int min, int max)
    {
        lv_slider_set_range(_slider, min, max);
        lv_slider_set_value(_slider, (max + min) / 2, LV_ANIM_ON);
    }

    void move(int x, int y)
    {
        lv_obj_set_x(_slider, x);
        lv_obj_set_y(_slider, y);
        lv_obj_align_to(_name_label, _slider, LV_ALIGN_LEFT_MID, -80, 0);
        lv_obj_align_to(_value_label, _slider, LV_ALIGN_RIGHT_MID, 50, 0);
    }

    void onValueChanged(std::function<void(int)> callback)
    {
        _on_value_changed = callback;
        lv_obj_add_event_cb(
            _slider,
            [](lv_event_t* e) {
                lv_obj_t* slider = (lv_obj_t*)lv_event_get_target(e);
                auto value = (int)lv_slider_get_value(slider);
                auto this_class = (Slider*)lv_event_get_user_data(e);
                if (this_class->_on_value_changed) {
                    this_class->_on_value_changed(value);
                }
                lv_label_set_text_fmt(this_class->_value_label, "%d", value);
            },
            LV_EVENT_VALUE_CHANGED, this);
    }

private:
    std::function<void(int)> _on_value_changed;
    lv_obj_t* _slider;
    lv_obj_t* _name_label;
    lv_obj_t* _value_label;
};

} // namespace lvgl
