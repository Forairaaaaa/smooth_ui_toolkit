/**
 * @file animate.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-08
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/raylib_wrapper.h"
#include <smooth_ui_toolkit.h>
#include <animation/animate/animate.h>
#include <mooncake_log.h>

using namespace smooth_ui_toolkit;
using namespace mooncake;

int main()
{
    Animate animation;

    // Animation options
    // Refs: https://motion.dev/docs/animate#options
    animation.start = 200;
    animation.end = 600;
    animation.repeat = -1;
    animation.repeatType = animate_repeat_type::reverse;
    animation.springOptions().bounce = 0.4;
    animation.springOptions().visualDuration = 0.6;

    // Callbacks
    animation.onUpdate([&](const float& value) { mclog::info("{}", value); });
    animation.onComplete([&]() { mclog::info("done"); });

    // Init and play
    animation.init();
    animation.play();

    raylib::create_window(800, 450, "你好", [&]() {
        // Update animation
        animation.update();

        // Render
        ClearBackground(BLACK);
        DrawCircle(animation.value(), 225, 30, LIGHTGRAY);
    });

    return 0;
}
