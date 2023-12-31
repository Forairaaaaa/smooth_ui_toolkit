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
        int x;
        int y;

        Vector2D_t(int x = 0, int y = 0)
        {
            reset(x, y);
        }

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

        Vector4D_t(int x = 0, int y = 0, int w = 0, int h = 0)
        {
            reset(x, y, w, h);
        }

        void reset(int x = 0, int y = 0, int w = 0, int h = 0)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
    };
}
