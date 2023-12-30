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
        int z;
        int w;

        Vector4D_t(int x = 0, int y = 0, int z = 0, int w = 0)
        {
            reset(x, y, z, w);
        }

        void reset(int x = 0, int y = 0, int z = 0, int w = 0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };
}
