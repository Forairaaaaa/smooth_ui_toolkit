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
    namespace EasingPath
    {
        // t: 0~maxT
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
    }
}
