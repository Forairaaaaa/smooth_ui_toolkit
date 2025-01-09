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
#include <animation/generators/spring/spring.h>
#include <animation/animate/animate.h>
#include <animation/animate_value/animate_value.h>
#include <animation/sequence/animate_value_sequence.h>
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{

    AnimateValueSequence anim_val = {50, 300, 600};

    anim_val.repeat = 1;
    anim_val.repeatType = animate_repeat_type::reverse;

    // AnimateValueSequence anim_val;

    // std::vector<int> sss = {50, 500, 100, 600, 300};
    // AnimateValueSequence anim_val = sss;

    // anim_val = {50, 500, 100, 600, 300};
    // anim_val = sss;

    // std::vector<int> sss = {50, 500, 100, 600, 300};
    // anim_val.setSequence(sss);

    // anim_val.setSequence({50, 500, 100, 600, 300});

    anim_val.play();

    raylib::create_window(800, 450, "你好👋", [&]() {
        ClearBackground(BLACK);
        mclog::info("{}", (float)anim_val);
        DrawCircle(anim_val, 225, 30, LIGHTGRAY);
    });

    return 0;
}
