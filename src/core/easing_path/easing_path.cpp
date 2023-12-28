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


using namespace SMOOTH_UI_TK::EasingPath;


EasingPath_t::EasingPath_t(float p0, float p1, float p2, float p3)
{
    _control_points.x = static_cast<int>(p0 * 1024);
    _control_points.y = static_cast<int>(p1 * 1024);
    _control_points.z = static_cast<int>(p2 * 1024);
    _control_points.w = static_cast<int>(p3 * 1024);
}
