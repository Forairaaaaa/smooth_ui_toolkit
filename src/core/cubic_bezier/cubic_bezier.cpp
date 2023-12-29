/**
 * @file cubic_bezier.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "cubic_bezier.h"


namespace SMOOTH_UI_TK
{
    int CubicBezierInt(int t, int p0, int p1, int p2, int p3)
    {
        int t_rem = 1024 - t;
        int t_rem2 = (t_rem * t_rem) >> 10;
        int t_rem3 = (t_rem2 * t_rem) >> 10;
        int t2 = (t * t) >> 10;
        int t3 = (t2 * t) >> 10;

        int v1 = (t_rem3 * p0) >> 10;
        int v2 = (3 * t_rem2 * t * p1) >> 20;
        int v3 = (3 * t_rem * t2 * p2) >> 20;
        int v4 = (t3 * p3) >> 10;

        return v1 + v2 + v3 + v4;
    }


    int CubicBezierInt(int t, Vector4D_t vector_4d)
    {
        int t_rem = 1024 - t;
        int t_rem2 = (t_rem * t_rem) >> 10;
        int t_rem3 = (t_rem2 * t_rem) >> 10;
        int t2 = (t * t) >> 10;
        int t3 = (t2 * t) >> 10;

        int v1 = (t_rem3 * vector_4d.x) >> 10;
        int v2 = (3 * t_rem2 * t * vector_4d.y) >> 20;
        int v3 = (3 * t_rem * t2 * vector_4d.z) >> 20;
        int v4 = (t3 * vector_4d.w) >> 10;

        return v1 + v2 + v3 + v4;
    }


    Vector4D_t cubicBezierCast2Int(float p0, float p1, float p2, float p3)
    {
        return Vector4D_t(
            static_cast<int>(p0 * 1024),
            static_cast<int>(p1 * 1024),
            static_cast<int>(p2 * 1024),
            static_cast<int>(p3 * 1024)
        );
    }
}
