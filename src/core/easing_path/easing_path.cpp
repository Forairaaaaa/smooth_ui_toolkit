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
#include "../../utils/fpm/math.hpp"


constexpr fpm::fixed_16_16 _c1 {1.70158};
constexpr fpm::fixed_16_16 _c2 {1.70158 * 1.525};
constexpr fpm::fixed_16_16 _c3 {1.70158 + 1};
constexpr fpm::fixed_16_16 _c4 {6.2831853 / 3};
constexpr fpm::fixed_16_16 _c5 {6.2831853 / 4.5};


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
        ft = ft * ft;
        return static_cast<int>(ft * maxT);
    }

    int easeOutQuad(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - (1 - ft) * (1 - ft);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutQuad(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = 2 * ft * ft;
        else
            ft = 1 - fpm::pow(-2 * ft + 2, 3) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInCubic(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = ft * ft * ft;
        return static_cast<int>(ft * maxT);
    }

    int easeOutCubic(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - fpm::pow(1 - ft, 3);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutCubic(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = 4 * ft * ft * ft;
        else
            ft = 1 - fpm::pow(-2 * ft + 2, 3) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInQuart(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = ft * ft * ft * ft;
        return static_cast<int>(ft * maxT);
    }

    int easeOutQuart(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - fpm::pow(1 - ft, 4);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutQuart(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = 8 * ft * ft * ft * ft;
        else
            ft = 1 - fpm::pow(-2 * ft + 2, 4) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInQuint(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = ft * ft * ft * ft * ft;
        return static_cast<int>(ft * maxT);
    }

    int easeOutQuint(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - fpm::pow(1 - ft, 5);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutQuint(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = 16 * ft * ft * ft * ft * ft;
        else
            ft = 1 - fpm::pow(-2 * ft + 2, 5) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInSine(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - fpm::cos((ft * ft.pi()) / 2);
        return static_cast<int>(ft * maxT);
    }

    int easeOutSine(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = fpm::sin((ft * ft.pi()) / 2);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutSine(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = -(fpm::cos(ft * ft.pi()) - 1) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInExpo(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t == 0)
            return 0;
        ft = fpm::pow(fpm::fixed_16_16 {2}, 10 * ft - 10);
        return static_cast<int>(ft * maxT);
    }

    int easeOutExpo(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t == maxT)
            return maxT;
        ft = 1 - fpm::pow(fpm::fixed_16_16 {2}, -10 * ft);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutExpo(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t == 0)
            return 0;
        if (t == maxT)
            return maxT;
        if (t < maxT / 2)
            ft = fpm::pow(fpm::fixed_16_16 {2}, 20 * ft - 10) / 2;
        else
            ft = (fpm::fixed_16_16 {2} - fpm::pow(fpm::fixed_16_16 {2}, -20 * ft + 10)) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInCirc(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 - fpm::sqrt(1 - fpm::pow(ft, 2));
        return static_cast<int>(ft * maxT);
    }

    int easeOutCirc(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = fpm::sqrt(1 - fpm::pow(ft - 1, 2));
        return static_cast<int>(ft * maxT);
    }

    int easeInOutCirc(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = (1 - fpm::sqrt(1 - fpm::pow(2 * ft, 2))) / 2;
        else
            ft = (fpm::sqrt(1 - fpm::pow(-2 * ft + 2, 2)) + 1) / 2;
        return static_cast<int>(ft * maxT);
    }

    int easeInBack(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = _c3 * ft * ft * ft - _c1 * ft * ft;
        return static_cast<int>(ft * maxT);
    }

    int easeOutBack(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        ft = 1 + _c3 * fpm::pow(ft - 1, 3) + _c1 * fpm::pow(ft - 1, 2);
        return static_cast<int>(ft * maxT);
    }

    int easeInOutBack(const int& t)
    {
        fpm::fixed_16_16 ft {t};
        ft = ft / maxT;
        if (t < maxT / 2)
            ft = (fpm::pow(2 * ft, 2) * ((_c2 + 1) * 2 * ft - _c2)) / 2;
        else
            ft = (fpm::pow(2 * ft - 2, 2) * ((_c2 + 1) * (ft * 2 - 2) + _c2) + 2) / 2;
        return static_cast<int>(ft * maxT);
    }

} }

