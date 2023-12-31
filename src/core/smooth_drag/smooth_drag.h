/**
 * @file smooth_drag.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../transition2d/transition2d.h"


namespace SmoothUIToolKit
{
    /**
     * @brief A class to provide drag and drop offset with transition 
     * 
     */
    class SmoothDrag;

    typedef void (*SmoothDragUpdateCallbackPtr)(SmoothDrag*);

    class SmoothDrag : public Transition2D
    {
    private:
        struct Data_t
        {
            Point_t drag_start_point;
            Point_t drag_start_offset;
            bool is_dragging = false;
        };
        Data_t _data;

    public:
        // Basic setter 
        inline void setUpdateCallback(SmoothDragUpdateCallbackPtr updateCallback)
        {
            Transition2D::setUpdateCallback(reinterpret_cast<Transition2DUpdateCallbackPtr>(updateCallback));
        }

        /**
         * @brief Start dragging 
         * 
         * @param x 
         * @param y 
         */
        void drag(const int& x, const int& y);
        inline void drag(const Point_t& p) { drag(p.x, p.y); }

        /**
         * @brief Stop dragging 
         * 
         */
        void drop();

        /**
         * @brief Get current drag and drop offset 
         * 
         * @return Point_t 
         */
        inline Point_t getOffset() { return getValue(); }
    };
}

