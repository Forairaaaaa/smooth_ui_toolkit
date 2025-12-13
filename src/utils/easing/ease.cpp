/**
 * @file ease.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-01-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "ease.hpp"
#include <cmath>

using namespace smooth_ui_toolkit;

float ease::linear(float t)
{
    return t;
};

float ease::ease_in_sine(float t)
{
    return 1 - std::cos((t * M_PI) / 2);
};
float ease::ease_out_sine(float t)
{
    return std::sin((t * M_PI) / 2);
};
float ease::ease_in_out_sine(float t)
{
    return -(std::cos(M_PI * t) - 1) / 2;
};

float ease::ease_in_quad(float t)
{
    return t * t;
};
float ease::ease_out_quad(float t)
{
    return 1 - (1 - t) * (1 - t);
};
float ease::ease_in_out_quad(float t)
{
    return t < 0.5 ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
};

float ease::ease_in_cubic(float t)
{
    return t * t * t;
};
float ease::ease_out_cubic(float t)
{
    return 1 - std::pow(1 - t, 3);
};
float ease::ease_in_out_cubic(float t)
{
    return t < 0.5 ? 4 * t * t * t : 1 - std::pow(-2 * t + 2, 3) / 2;
};

float ease::ease_in_quart(float t)
{
    return t * t * t * t;
};
float ease::ease_out_quart(float t)
{
    return 1 - std::pow(1 - t, 4);
};
float ease::ease_in_out_quart(float t)
{
    return t < 0.5 ? 8 * t * t * t * t : 1 - std::pow(-2 * t + 2, 4) / 2;
};

float ease::ease_in_quint(float t)
{
    return t * t * t * t * t;
};
float ease::ease_out_quint(float t)
{
    return 1 - std::pow(1 - t, 5);
};
float ease::ease_in_out_quint(float t)
{
    return t < 0.5 ? 16 * t * t * t * t * t : 1 - std::pow(-2 * t + 2, 5) / 2;
};

float ease::ease_in_expo(float t)
{
    return t == 0 ? 0 : std::pow(2, 10 * t - 10);
};
float ease::ease_out_expo(float t)
{
    return t == 1 ? 1 : 1 - std::pow(2, -10 * t);
};
float ease::ease_in_out_expo(float t)
{
    if (t == 0) {
        return 0.0;
    }
    if (t == 1) {
        return 1.0;
    }
    if (t < 0.5) {
        return std::pow(2, 20 * t - 10) / 2;
    }
    return (2 - std::pow(2, -20 * t + 10)) / 2;
};

float ease::ease_in_circ(float t)
{
    return 1 - std::sqrt(1 - std::pow(t, 2));
};
float ease::ease_out_circ(float t)
{
    return std::sqrt(1 - std::pow(t - 1, 2));
};
float ease::ease_in_out_circ(float t)
{
    return t < 0.5 ? (1 - std::sqrt(1 - std::pow(2 * t, 2))) / 2 : (std::sqrt(1 - std::pow(-2 * t + 2, 2)) + 1) / 2;
};

float ease::ease_in_back(float t)
{
    constexpr float c1 = 1.70158;
    constexpr float c3 = c1 + 1;
    return c3 * t * t * t - c1 * t * t;
};
float ease::ease_out_back(float t)
{
    constexpr float c1 = 1.70158;
    constexpr float c3 = c1 + 1;
    return 1 + c3 * std::pow(t - 1, 3) + c1 * std::pow(t - 1, 2);
};
float ease::ease_in_out_back(float t)
{
    constexpr float c1 = 1.70158;
    constexpr float c2 = c1 * 1.525;
    return t < 0.5 ? (std::pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
                   : (std::pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
};

float ease::ease_in_elastic(float x)
{
    constexpr float c4 = (2 * M_PI) / 3;
    return x == 0 ? 0 : x == 1 ? 1 : -std::pow(2, 10 * x - 10) * std::sin((x * 10 - 10.75) * c4);
};
float ease::ease_out_elastic(float x)
{
    constexpr float c4 = (2 * M_PI) / 3;
    return x == 0 ? 0 : x == 1 ? 1 : std::pow(2, -10 * x) * std::sin((x * 10 - 0.75) * c4) + 1;
};
float ease::ease_in_out_elastic(float x)
{
    constexpr float c5 = (2 * M_PI) / 4.5;
    return x == 0    ? 0
           : x == 1  ? 1
           : x < 0.5 ? -std::pow(2, 20 * x - 10) * std::sin((20 * x - 11.125) * c5) / 2
                     : std::pow(2, -20 * x + 10) * std::sin((20 * x - 11.125) * c5) / 2 + 1;
};

float ease::ease_out_bounce(float t)
{
    constexpr float n1 = 7.5625;
    constexpr float d1 = 2.75;

    if (t < 1 / d1) {
        return n1 * t * t;
    } else if (t < 2 / d1) {
        t -= 1.5 / d1;
        return n1 * t * t + 0.75;
    } else if (t < 2.5 / d1) {
        t -= 2.25 / d1;
        return n1 * t * t + 0.9375;
    } else {
        t -= 2.625 / d1;
        return n1 * t * t + 0.984375;
    }
}
float ease::ease_in_bounce(float t)
{
    return 1 - ease_out_bounce(1 - t);
};
float ease::ease_in_out_bounce(float t)
{
    return t < 0.5 ? (1 - ease_out_bounce(1 - 2 * t)) / 2 : (1 + ease_out_bounce(2 * t - 1)) / 2;
}