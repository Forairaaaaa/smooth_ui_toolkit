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

namespace SmoothUIToolKit
{
    bool IsInRange(Vector2D_t range, int x);
    int GetRange(Vector2D_t range);
    int Clamp(int value, Vector2D_t range);
    int Clamp(int value, Vector2D_t range, bool& isInRange);
} // namespace SmoothUIToolKit
