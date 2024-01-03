/**
 * @file widget_base.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "../../core/types/types.h"


namespace SmoothUIToolKit 
{ 
    namespace SmoothWidget 
    {
        class WidgetBase
        {
        protected:
            // x, y
            Vector2D_t _position;
            // w, h
            Vector2D_t _size;

        public:
            WidgetBase() = default;
            WidgetBase(int x, int y, int width, int height)
            {
                _position.reset(x, y);
                _size.reset(width, height);
            }
            WidgetBase(Vector2D_t position, Vector2D_t size)
            {
                _position = position;
                _size = size;
            }

            /**
             * @brief Tell widget what time is it and update 
             * 
             * @param currentTime 
             */
            virtual void update(std::uint32_t currentTime) {}

            /**
             * @brief Tell widget where the cursor is now 
             * 
             * @param x 
             * @param y 
             */
            virtual void hover(int x, int y) {}

            /**
             * @brief Tell widget where the pressing cursor is now 
             * 
             * @param x 
             * @param y 
             */
            virtual void drag(int x, int y) {}

            /**
             * @brief Tell widget cursor just released 
             * 
             */
            virtual void drop() {}
        };
    }
}
