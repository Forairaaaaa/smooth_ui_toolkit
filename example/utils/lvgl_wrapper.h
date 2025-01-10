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
}

void update_window()
{
    lv_timer_handler();
}

} // namespace lvgl
