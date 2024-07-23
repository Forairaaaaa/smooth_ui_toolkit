/**
 * @file color.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-07-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../../utils/fpm/fixed.hpp"
#include "../../utils/fpm/math.hpp"
#include "core/types/types.h"
#include "math.h"

SmoothUIToolKit::RGB_t SmoothUIToolKit::Hex2Rgb(std::uint32_t color)
{
    return RGB_t((color >> 16) & 0x0000FF, (color >> 8) & 0x0000FF, color & 0x0000FF);
}

std::uint32_t SmoothUIToolKit::Rgb2Hex(RGB_t color)
{
    return ((color.red & 0xff) << 16) + ((color.green & 0xff) << 8) + (color.blue & 0xff);
}

SmoothUIToolKit::RGB_t SmoothUIToolKit::BlendColorInDifference(RGB_t bgColor, RGB_t fgColor)
{
    // 计算差值
    uint8_t resultRed = std::abs(bgColor.red - fgColor.red);
    uint8_t resultGreen = std::abs(bgColor.green - fgColor.green);
    uint8_t resultBlue = std::abs(bgColor.blue - fgColor.blue);

    RGB_t ret;
    ret.reset(resultRed, resultGreen, resultBlue);
    return ret;
}

std::uint32_t SmoothUIToolKit::BlendColorInDifference(std::uint32_t bgColor, std::uint32_t fgColor)
{
    return Rgb2Hex(BlendColorInDifference(Hex2Rgb(bgColor), Hex2Rgb(fgColor)));
}
