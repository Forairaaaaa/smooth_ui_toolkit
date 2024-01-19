/**
 * @file smooth_color.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../transition/transition.h"
#include "../types/types.h"

namespace SmoothUIToolKit
{
    class SmoothColor
    {
    private:
        struct Data_t
        {
            Transition r_transition;
            Transition g_transition;
            Transition b_transition;
        };
        Data_t _data;

    public:
        // Basic setter
        inline void setDuration(TimeSize_t duration)
        {
            _data.r_transition.setDuration(duration);
            _data.g_transition.setDuration(duration);
            _data.b_transition.setDuration(duration);
        }
        inline void setDelay(TimeSize_t delay)
        {
            _data.r_transition.setDelay(delay);
            _data.g_transition.setDelay(delay);
            _data.b_transition.setDelay(delay);
        }
        inline void setTransitionPath(EasingPathPtr transitionPath)
        {
            _data.r_transition.setTransitionPath(transitionPath);
            _data.g_transition.setTransitionPath(transitionPath);
            _data.b_transition.setTransitionPath(transitionPath);
        }

    public:
        void update(const TimeSize_t& currentTime);
    };
} // namespace SmoothUIToolKit
