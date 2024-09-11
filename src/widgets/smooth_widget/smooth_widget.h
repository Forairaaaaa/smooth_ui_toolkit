/**
 * @file smooth_widget.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/transition4d/transition4d.h"
#include "../base/base.h"
#include <functional>
#include <vector>

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        /**
         * @brief Provide widget base with x, y, w, h transition
         *
         */
        class SmoothWidgetBase : public WidgetBase
        {
        protected:
            struct SmoothBaseData_t
            {
                Transition4D transition;

                // Transition direction
                bool is_hiding = true;
            };
            SmoothBaseData_t _smooth_base_data;

        public:
            SmoothWidgetBase() = default;
            SmoothWidgetBase(SmoothWidgetBase* parent) : WidgetBase((WidgetBase*)parent) {}
            virtual ~SmoothWidgetBase() {}

            // Helper getter
            inline Transition4D& getTransition() { return _smooth_base_data.transition; }

            /**
             * @brief Pop out widget
             *
             */
            virtual void popOut();

            /**
             * @brief Hide widget
             *
             */
            virtual void hide();

            /**
             * @brief Is transition finished
             *
             * @return true
             * @return false
             */
            virtual bool isTransitionFinish() { return _smooth_base_data.transition.isFinish(); }

            /**
             * @brief Is widget completely isHidden
             *
             * @return true
             * @return false
             */
            virtual bool isHidden();

            /**
             * @brief Is widget completely popped out
             *
             * @return true
             * @return false
             */
            virtual bool isPoppedOut();

            /**
             * @brief Is widget hidding currently
             *
             * @return true
             * @return false
             */
            virtual bool isHidding();

            /**
             * @brief Is widget popping out currently
             *
             * @return true
             * @return false
             */
            virtual bool isPoppingOut();

            /**
             * @brief Update transition
             *
             * @param currentTime
             */
            virtual void updateTransition(const TimeSize_t& currentTime);

            using WidgetBase::update;

            /**
             * @brief Update widget with transition update
             *
             * @param currentTime
             */
            virtual void update(const TimeSize_t& currentTime);

            /* -------------------------------------------------------------------------- */
            /*                                  Callbacks                                 */
            /* -------------------------------------------------------------------------- */
        public:
            /**
             * @brief Setup your pop out transition
             *
             */
            virtual void onPopOut() {}

            /**
             * @brief Setup your hiding transition
             *
             */
            virtual void onHide() {}
        };
    } // namespace Widgets
} // namespace SmoothUIToolKit
