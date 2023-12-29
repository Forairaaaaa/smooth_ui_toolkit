/**
 * @file cubic_bezier.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-28
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
    /**
     * @brief Cubic bezier in integer, t: 0~1024
     * 
     * @param t 
     * @param p0 
     * @param p1 
     * @param p2 
     * @param p3 
     * @return int 
     */
    int CubicBezierInt(int t, int p0, int p1, int p2, int p3);
    
    /**
     * @brief Cubic bezier in integer, t: 0~1024
     * 
     * @param t 
     * @param vector_4d 
     * @return int 
     */
    int CubicBezierInt(int t, Vector4D_t vector_4d);
    
    /**
     * @brief Cast normal cubic bezier to integer 
     * 
     * @param p0 
     * @param p1 
     * @param p2 
     * @param p3 
     * @return Vector4D_t 
     */
    Vector4D_t cubicBezierCast2Int(float p0, float p1, float p2, float p3);
}
