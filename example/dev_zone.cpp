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
#include "utils/raylib_wrapper.h"
#include "raylib.h"
#include "utils/hal/hal.h"
#include "utils/lvgl_wrapper.h"
#include <animation/generators/spring/spring.h>
#include <animation/animate/animate.h>
#include <animation/animate_value/animate_value.h>
#include <animation/sequence/animate_value_sequence.h>
#include <src/core/lv_obj.h>
#include <src/core/lv_obj_pos.h>
#include <src/core/lv_obj_style_gen.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_area.h>
#include <utils/easing/ease.h>
#include <lvgl.h>
#include <thread>
#include <vector>
#include <lvgl/lvgl_cpp/obj.hpp>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    lvgl::create_window(800, 480);

    lvgl_cpp::LvObject obj;
    obj.setPos(100, 100);
    obj.setSize(200, 200);
    obj.setBgColor(lv_color_make(0x00, 0x00, 0xFF));
    obj.setRadius(20);
    obj.setBorderWidth(5);
    obj.setBorderColor(lv_color_make(0xFF, 0x00, 0x00));
    obj.setRotation(45);
    obj.setScrollbarMode(LV_SCROLLBAR_MODE_OFF);

    while (1) {
        lvgl::update_window();
    }

    return 0;
}
