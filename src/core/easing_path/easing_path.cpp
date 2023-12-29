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
#include "../../utils/fpm/fixed.hpp"


namespace SMOOTH_UI_TK { namespace EasingPath
{
    int linear(const int& t)
    {
        return t;
    }

    int easeInQuad(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = ft * ft * maxT;
        return static_cast<int>(ft);
    }

    int easeOutQuad(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - ft;
        ft = ft * ft;
        ft = 1 - ft;
        ft = ft * maxT;
        return static_cast<int>(ft);
    }

} }

