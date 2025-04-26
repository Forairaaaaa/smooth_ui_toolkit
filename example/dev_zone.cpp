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
// git update-index --skip-worktree example/dev_zone.cpp
#include "utils/lvgl_wrapper.h"
#include "utils/raylib_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <smooth_lvgl.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;
using namespace smooth_ui_toolkit::lvgl_cpp;

static void raylib_window()
{
    raylib::create_window(800, 450, "你好", [&]() {
        // Render
        ClearBackground(RAYWHITE);
    });
}

static void lvgl_window()
{
    lvgl::create_window(800, 520);

    while (1) {
        lvgl::update_window();
    }
}

int main()
{
    raylib_window();
    // lvgl_window();
    return 0;
}