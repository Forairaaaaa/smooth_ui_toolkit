/**
 * @file select_menu_base.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/types/types.h"

namespace SmoothUIToolKit
{
    namespace SelectMenu
    {
        /**
         * @brief Base class of select menu.
         * Provide common methods and callbacks declare 
         *
         */
        class SelectMenuBase
        {
        public:
            virtual void goLast() {}
            virtual void goNext() {}
            virtual void update(const TimeSize_t& currentTime) {}

        public:
            virtual void onGoLast() {}
            virtual void onGoNext() {}
            virtual void onPress() {}
            virtual void onRelease() {}
            virtual void onClick() {}
            virtual void onOpenEnd() {}
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onReadInput() {}
            virtual void onRender() {}
        };
    } // namespace SelectMenu
} // namespace SmoothUIToolKit
