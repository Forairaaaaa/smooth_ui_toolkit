/**
 * @file easing_path.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "easing_path.h"
#include "../cubic_bezier/cubic_bezier.h"


namespace SMOOTH_UI_TK::EasingPath
{
    // Cubic bezier paths 
    int easeInSine(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.12, 0, 0.39, 0)); }
    int easeOutSine(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.61, 1, 0.88, 1)); }
    int easeInOutSine(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.37, 0, 0.63, 1)); }
    int easeInQuad(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.11, 0, 0.5, 0)); }
    int easeOutQuad(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.5, 1, 0.89, 1)); }
    int easeInOutQuad(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.45, 0, 0.55, 1)); }
    int easeInCubic(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.32, 0, 0.67, 0)); }
    int easeOutCubic(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.33, 1, 0.68, 1)); }
    int easeInOutCubic(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.65, 0, 0.35, 1)); }
    int easeInQuart(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.5, 0, 0.75, 0)); }
    int easeOutQuart(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.25, 1, 0.5, 1)); }
    int easeInOutQuart(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.76, 0, 0.24, 1)); }
    int easeInQuint(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.64, 0, 0.78, 0)); }
    int easeOutQuint(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.22, 1, 0.36, 1)); }
    int easeInOutQuint(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.83, 0, 0.17, 1)); }
    int easeInExpo(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.7, 0, 0.84, 0)); }
    int easeOutExpo(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.16, 1, 0.3, 1)); }
    int easeInOutExpo(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.87, 0, 0.13, 1)); }
    int easeInCirc(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.55, 0, 1, 0.45)); }
    int easeOutCirc(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0, 0.55, 0.45, 1)); }
    int easeInOutCirc(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.85, 0, 0.15, 1)); }
    int easeInBack(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.36, 0, 0.66, -0.56)); }
    int easeOutBack(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.34, 1.56, 0.64, 1)); }
    int easeInOutBack(int t) { return CubicBezierInt(t, cubicBezierCast2Int(0.68, -0.6, 0.32, 1.6)); }

    // Special paths 

}

