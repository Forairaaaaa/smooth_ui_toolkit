/**
 * @file types.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <cstdint>

namespace SmoothUIToolKit
{
    struct Vector2D_t
    {
        union
        {
            int x;
            int width;
        };
        union
        {
            int y;
            int height;
        };

        Vector2D_t(int x = 0, int y = 0) { reset(x, y); }

        void reset(int x = 0, int y = 0)
        {
            this->x = x;
            this->y = y;
        }
    };

    struct Vector4D_t
    {
        int x;
        int y;
        int w;
        int h;

        Vector4D_t(int x = 0, int y = 0, int w = 0, int h = 0) { reset(x, y, w, h); }

        void reset(int x = 0, int y = 0, int w = 0, int h = 0)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
    };

    typedef std::uint32_t TimeSize_t;

    inline bool IsInRange(Vector2D_t range, int x)
    {
        if (x < range.x)
            return false;
        if (x > range.y)
            return false;
        return true;
    }

    inline int GetRange(Vector2D_t range)
    {
        if (range.x > range.y)
            return range.x - range.y;
        return range.y - range.x;
    }

    inline int Clamp(int value, Vector2D_t range)
    {
        if (value < range.x)
            return range.x;
        if (value > range.y)
            return range.y;
        return value;
    }

    inline int Clamp(int value, Vector2D_t range, bool& isInRange)
    {
        isInRange = false;
        if (value < range.x)
            return range.x;
        if (value > range.y)
            return range.y;
        isInRange = true;
        return value;
    }
} // namespace SmoothUIToolKit
