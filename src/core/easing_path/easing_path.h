/**
 * @file easing_path.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "../types/types.h"
#include <functional>
// Refs:
// https://cubic-bezier.com/#.17,.67,.83,.67
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve
// https://github.com/ai/easings.net/blob/master/src/easings/easingsFunctions.ts
// https://easings.net
// https://mikelankamp.github.io/fpm/
// https://www.desmos.com/calculator?lang=zh-CN

namespace SmoothUIToolKit
{
    namespace EasingPath
    {
        // t: 0 ~ maxT
        constexpr int maxT = 1000;

        int linear(const int& t);
        int easeInQuad(const int& t);
        int easeOutQuad(const int& t);
        int easeInOutQuad(const int& t);
        int easeInCubic(const int& t);
        int easeOutCubic(const int& t);
        int easeInOutCubic(const int& t);
        int easeInQuart(const int& t);
        int easeOutQuart(const int& t);
        int easeInOutQuart(const int& t);
        int easeInQuint(const int& t);
        int easeOutQuint(const int& t);
        int easeInOutQuint(const int& t);
        int easeInSine(const int& t);
        int easeOutSine(const int& t);
        int easeInOutSine(const int& t);
        int easeInExpo(const int& t);
        int easeOutExpo(const int& t);
        int easeInOutExpo(const int& t);
        int easeInCirc(const int& t);
        int easeOutCirc(const int& t);
        int easeInOutCirc(const int& t);
        int easeInBack(const int& t);
        int easeOutBack(const int& t);
        int easeInOutBack(const int& t);
        int easeInElastic(const int& t);
        int easeOutElastic(const int& t);
        int easeInOutElastic(const int& t);
        int easeInBounce(const int& t);
        int easeOutBounce(const int& t);
        int easeInOutBounce(const int& t);
    } // namespace EasingPath

    typedef std::function<int(const int&)> EasingPath_t;

} // namespace SmoothUIToolKit
