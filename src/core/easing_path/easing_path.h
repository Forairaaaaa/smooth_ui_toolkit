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
// Refs: 
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve
// https://github.com/ai/easings.net/blob/master/src/easings/easingsFunctions.ts
// https://easings.net
// https://mikelankamp.github.io/fpm/


namespace SMOOTH_UI_TK
{
    // Paths, t: 0~100
    namespace EasingPath
    {
        constexpr int maxT = 1000;
        int linear(const int& t);
        int easeInQuad(const int& t);
        int easeOutQuad(const int& t);
    }
}
