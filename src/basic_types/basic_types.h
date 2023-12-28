/**
 * @file basic_types.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once


namespace SMOOTH_UI_TK
{
    struct Point2D_Int_t
    {
        int x;
        int y;

        Point2D_Int_t(int x = 0, int y = 0)
        {
            reset(x, y);
        }

        void reset(int x = 0, int y = 0)
        {
            this->x = x;
            this->y = y;
        }
    };
}
