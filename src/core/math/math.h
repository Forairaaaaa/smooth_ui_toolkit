/**
 * @file math.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../types/types.h"
#include <cstdint>

namespace SmoothUIToolKit
{
    // Range
    bool IsInRange(Vector2D_t range, int x);
    int GetRange(Vector2D_t range);
    int Clamp(int value, Vector2D_t range);
    int Clamp(int value, Vector2D_t range, bool& isInRange);

    // Color
    RGB_t Hex2Rgb(std::uint32_t color);
    std::uint32_t Rgb2Hex(RGB_t color);
} // namespace SmoothUIToolKit
