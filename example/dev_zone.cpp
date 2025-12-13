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
#include "utils/lvgl_wrapper.hpp"
#include "utils/raylib_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>
#include <smooth_lvgl.hpp>
#include <mooncake_log.h>

using namespace uitk;
using namespace uitk::lvgl_cpp;

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