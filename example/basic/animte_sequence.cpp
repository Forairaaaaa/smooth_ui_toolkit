/**
 * @file animte_sequence.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-04-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../utils/lvgl_wrapper.hpp"
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>
#include <smooth_lvgl.hpp>
#include <mooncake_log.h>

using namespace uitk;
using namespace uitk::lvgl_cpp;

std::vector<double> generate_damping_sine_sequence(double start_amp, double end_amp, int num_extremes)
{
    std::vector<double> extremes;

    // Start value
    extremes.push_back(0);

    for (int i = 0; i < num_extremes; ++i) {
        double t_ratio = static_cast<double>(i) / (num_extremes - 1); // 归一化时间 (0~1)
        double amp = start_amp + (end_amp - start_amp) * t_ratio;     // 线性衰减
        extremes.push_back((i % 2 == 0) ? amp : -amp);                // 交替存储波峰和波谷
    }

    return extremes;
}

int main()
{
    lvgl::create_window(800, 520);

    auto shake_box = Container(lv_screen_active());
    shake_box.setAlign(LV_ALIGN_CENTER);

    auto shake_anim = AnimateSequence();
    shake_anim.setSequence(generate_damping_sine_sequence(100, 0, 20));
    shake_anim.repeat = -1;
    shake_anim.onStep([&](AnimateValue& animateValue, std::vector<float>& values, int step) {
        // Setup animation options on callback
        animateValue.delay = (step == 1) ? 1 : 0;
        animateValue.easingOptions().duration = 0.12;
    });
    shake_anim.play();

    while (1) {
        // Apply animation
        shake_box.setPos(shake_anim, -20);

        lvgl::update_window();
    }

    return 0;
}
