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
// https://cubic-bezier.com
// https://easings.net
// https://github.com/lvgl/lvgl/blob/master/src/misc/lv_anim.h


namespace SMOOTH_UI_TK
{
    namespace EasingPath
    {
        // Paths 
        int easeInSine(int t);
        int easeOutSine(int t);
        int easeInOutSine(int t);
        int easeInQuad(int t);
        int easeOutQuad(int t);
        int easeInOutQuad(int t);
        int easeInCubic(int t);
        int easeOutCubic(int t);
        int easeInOutCubic(int t);
        int easeInQuart(int t);
        int easeOutQuart(int t);
        int easeInOutQuart(int t);
        int easeInQuint(int t);
        int easeOutQuint(int t);
        int easeInOutQuint(int t);
        int easeInExpo(int t);
        int easeOutExpo(int t);
        int easeInOutExpo(int t);
        int easeInCirc(int t);
        int easeOutCirc(int t);
        int easeInOutCirc(int t);
        int easeInBack(int t);
        int easeOutBack(int t);
        int easeInOutBack(int t);
    }
}
