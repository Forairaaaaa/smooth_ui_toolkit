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
#include <functional>

namespace SmoothUIToolKit
{
    /* -------------------------------------------------------------------------- */
    /*                                    Range                                   */
    /* -------------------------------------------------------------------------- */
    bool IsInRange(Vector2D_t range, int x);
    int GetRange(Vector2D_t range);
    int Clamp(int value, Vector2D_t range);
    int Clamp(int value, Vector2D_t range, bool& isInRange);

    /* -------------------------------------------------------------------------- */
    /*                                    Color                                   */
    /* -------------------------------------------------------------------------- */
    RGB_t Hex2Rgb(std::uint32_t color);
    std::uint32_t Rgb2Hex(RGB_t color);
    RGB_t BlendColorInDiffernce(RGB_t bgColor, RGB_t fgColor);
    std::uint32_t BlendColorInDiffernce(std::uint32_t bgColor, std::uint32_t fgColor);

    /* -------------------------------------------------------------------------- */
    /*                                   Graphic                                  */
    /* -------------------------------------------------------------------------- */
    void DrawLineAA(int x0, int y0, int x1, int y1, std::function<void(const int& x, const int& y, const int& t)> plotCallback);
    void DrawLineAAWidth(
        int x0, int y0, int x1, int y1, int width, std::function<void(const int& x, const int& y, const int& t)> plotCallback);
} // namespace SmoothUIToolKit
