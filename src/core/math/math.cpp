/**
 * @file math.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "math.h"
#include "core/types/types.h"

bool SmoothUIToolKit::IsInRange(Vector2D_t range, int x)
{
    if (x < range.x)
        return false;
    if (x > range.y)
        return false;
    return true;
}

int SmoothUIToolKit::GetRange(Vector2D_t range)
{
    if (range.x > range.y)
        return range.x - range.y;
    return range.y - range.x;
}

int SmoothUIToolKit::Clamp(int value, Vector2D_t range)
{
    if (value < range.x)
        return range.x;
    if (value > range.y)
        return range.y;
    return value;
}

int SmoothUIToolKit::Clamp(int value, Vector2D_t range, bool& isInRange)
{
    isInRange = false;
    if (value < range.x)
        return range.x;
    if (value > range.y)
        return range.y;
    isInRange = true;
    return value;
}

SmoothUIToolKit::RGB_t SmoothUIToolKit::Hex2Rgb(std::uint32_t color)
{
    return RGB_t((color >> 16) & 0x0000FF, (color >> 8) & 0x0000FF, color & 0x0000FF);
}

std::uint32_t SmoothUIToolKit::Rgb2Hex(RGB_t color)
{
    return ((color.red & 0xff) << 16) + ((color.green & 0xff) << 8) + (color.blue & 0xff);
}
