/**
 * @file basic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <smooth_ui_toolkit.h>
#include <iostream>
#include <animation/generators/spring/spring.h>

using namespace smooth_ui_toolkit;

int main()
{
    Spring anim;

    anim.animationOptions.start = 0;
    anim.animationOptions.end = 100;
    // anim.springOptions.stiffness = 150;
    // anim.springOptions.damping = 20;
    // anim.springOptions.mass = 1;

    anim.init();

    double t = 0.0;    // 时间
    double dt = 0.016; // 时间步长 (模拟60fps)

    // 模拟动画
    while (!anim.next(t).done) {
        std::cout << "Time: " << t << " Value: " << anim.getState().value << std::endl;
        t += dt;
    }

    std::cout << "Final Value: " << anim.getState().value << std::endl;

    return 0;
}
