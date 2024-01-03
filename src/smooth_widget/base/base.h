/**
 * @file base.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "../../core/transition2d/transition2d.h"


namespace SmoothUIToolKit 
{ 
    namespace SmoothWidget 
    {
        class WidgetBase
        {
        protected:
            // x, y
            Transition2D position;
            // w, h
            Transition2D shape;

        public:
            inline const Transition2D& getPostion() { return position; }
            inline const Transition2D& getShape() { return shape; }

            /**
             * @brief Widget update method 
             * 
             * @param currentTime 
             */
            virtual void update(std::uint32_t currentTime) {}
        };
    }
}
