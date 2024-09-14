/**
 * @file graphic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../../utils/fpm/fixed.hpp"
#include "../../utils/fpm/math.hpp"
#include "core/types/types.h"
#include "math.h"
#include <algorithm>
#include <cmath>
// Refs:
// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
// http://members.chello.at/~easyfilter/bresenham.html

void SmoothUIToolKit::DrawLineAA(
    int x0, int y0, int x1, int y1, std::function<void(const int& x, const int& y, const int& t)> plotCallback)
{
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy, e2, x2; /* error value e_xy */
    int ed = dx + dy == 0 ? 1 : static_cast<int>(fpm::sqrt(fpm::fixed_24_8{dx * dx + dy * dy}));

    /* pixel loop */
    for (;;)
    {
        plotCallback(x0, y0, 255 * std::abs(err - dx + dy) / ed);
        e2 = err;
        x2 = x0;
        if (2 * e2 >= -dx)
        { /* x step */
            if (x0 == x1)
                break;
            if (e2 + dy < ed)
                // setPixelAA(x0, y0 + sy, 255 * (e2 + dy) / ed);
                plotCallback(x0, y0 + sy, 255 * (e2 + dy) / ed);
            err -= dy;
            x0 += sx;
        }
        if (2 * e2 <= dy)
        { /* y step */
            if (y0 == y1)
                break;
            if (dx - e2 < ed)
                plotCallback(x2 + sx, y0, 255 * (dx - e2) / ed);
            err += dx;
            y0 += sy;
        }
    }
}

void SmoothUIToolKit::DrawLineAAWidth(
    int x0, int y0, int x1, int y1, int width, std::function<void(const int& x, const int& y, const int& t)> plotCallback)
{
    int dx = std::abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = std::abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx - dy, e2, x2, y2; /* error value e_xy */
    // float ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);
    fpm::fixed_24_8 f_ed;
    if (dx + dy == 0)
        f_ed = fpm::fixed_24_8{1};
    else
        f_ed = fpm::sqrt(fpm::fixed_24_8{dx * dx + dy * dy});
    fpm::fixed_24_8 f_t;

    /* pixel loop */
    for (width = (width + 1) / 2;;)
    {
        f_t = 255 * (fpm::fixed_24_8{std::abs(err - dx + dy)} / f_ed - width + 1);
        plotCallback(x0, y0, std::max(0, static_cast<int>(f_t)));

        e2 = err;
        x2 = x0;
        if (2 * e2 >= -dx)
        { /* x step */
            for (e2 += dy, y2 = y0; fpm::fixed_24_8{e2} < f_ed * width && (y1 != y2 || dx > dy); e2 += dx)
            {
                f_t = 255 * (fpm::fixed_24_8{std::abs(e2)} / f_ed - width + 1);
                plotCallback(x0, y2 += sy, std::max(0, static_cast<int>(f_t)));
            }
            if (x0 == x1)
                break;
            e2 = err;
            err -= dy;
            x0 += sx;
        }
        if (2 * e2 <= dy)
        { /* y step */
            for (e2 = dx - e2; fpm::fixed_24_8{e2} < f_ed * width && (x1 != x2 || dx < dy); e2 += dy)
            {
                f_t = 255 * (fpm::fixed_24_8{std::abs(e2)} / f_ed - width + 1);
                plotCallback(x2 += sx, y0, std::max(0, static_cast<int>(f_t)));
            }
            if (y0 == y1)
                break;
            err += dx;
            y0 += sy;
        }
    }
}
