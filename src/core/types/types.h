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

        bool equals(int x, int y)
        {
            if (x != this->x)
                return false;
            if (y != this->y)
                return false;
            return true;
        }
    };

    struct Vector3D_t
    {
        union
        {
            int x;
            int red;
        };
        union
        {
            int y;
            int green;
        };
        union
        {
            int z;
            int blue;
        };

        Vector3D_t(int x = 0, int y = 0, int z = 0) { reset(x, y, z); }

        void reset(int x = 0, int y = 0, int z = 0)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        bool equals(int x, int y, int z)
        {
            if (x != this->x)
                return false;
            if (y != this->y)
                return false;
            if (z != this->z)
                return false;
            return true;
        }
    };

    typedef Vector3D_t RGB_t;

    struct Vector4D_t
    {
        union
        {
            int x;
            int red;
        };
        union
        {
            int y;
            int green;
        };
        union
        {
            int w;
            int blue;
        };
        union
        {
            int h;
            int alpha;
        };

        Vector4D_t(int x = 0, int y = 0, int w = 0, int h = 0) { reset(x, y, w, h); }

        void reset(int x = 0, int y = 0, int w = 0, int h = 0)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }

        bool equals(int x, int y, int w, int h)
        {
            if (x != this->x)
                return false;
            if (y != this->y)
                return false;
            if (w != this->w)
                return false;
            if (h != this->h)
                return false;
            return true;
        }
    };

    typedef Vector4D_t RGBA_t;

    typedef std::uint32_t TimeSize_t;

    struct VectorFloat2D_t
    {
        union
        {
            float x;
            float width;
        };
        union
        {
            float y;
            float height;
        };

        VectorFloat2D_t(float x = 0, float y = 0) { reset(x, y); }

        void reset(float x = 0, float y = 0)
        {
            this->x = x;
            this->y = y;
        }
    };
} // namespace SmoothUIToolKit
