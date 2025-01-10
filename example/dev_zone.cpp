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

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    lvgl::create_window(800, 450);

    auto shit = lv_obj_create(lv_screen_active());
    lv_obj_set_align(shit, LV_ALIGN_CENTER);
    lv_obj_set_size(shit, 140, 140);
    lv_obj_set_style_transform_pivot_x(shit, 140 / 2, LV_PART_MAIN);
    lv_obj_set_style_transform_pivot_y(shit, 140 / 2, LV_PART_MAIN);

    int i = 0;
    while (1) {
        lv_obj_set_style_transform_rotation(shit, i += 5, LV_PART_MAIN);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        lvgl::update_window();
    }

    return 0;
}
