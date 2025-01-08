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
#include <utils/easing/ease.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    // Spring anim;
    // anim.start = 50;
    // anim.end = 600;

    // anim.springOptions.duration = 1000;
    // anim.springOptions.bounce = 0.3;
    // anim.springOptions.visualDuration = 0.8;

    Animate anim;
    anim.start = 200;
    anim.end = 600;
    anim.delay = 0.8;
    // anim.repeat = 3;
    // anim.repeatDelay = 1.0;
    // anim.repeatType = animate_repeat_type::loop;
    anim.repeatType = animate_repeat_type::reverse;
    // anim.repeatType = animate_repeat_type::mirror;

    anim.springOptions().duration = 1000;
    anim.springOptions().bounce = 0.4;
    anim.springOptions().visualDuration = 0.6;

    float shit = 0;
    anim.onUpdate([&](const float& value) {
        // mclog::info("{}", value);
        shit = value;

        static bool retargeted = false;
        if ((int)value == 600 && !retargeted) {
            mclog::info("retargeted");
            retargeted = true;
            anim.retarget(value, 300);
        }
    });
    anim.onComplete([&]() {
        mclog::info("boom");
        // anim.cancel();
        // anim.play();
    });

    anim.init();
    anim.play();
    // anim.cancel();
    // anim.complete();
    // anim.pause();
    // ui_hal::delay_s(3);
    // anim.play();

    raylib::create_window(800, 450, "你好👋", [&]() {
        anim.update();

        ClearBackground(BLACK);
        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawCircle(shit, 225, 30, LIGHTGRAY);
    });

    return 0;
}
