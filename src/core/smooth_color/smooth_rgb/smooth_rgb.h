/**
 * @file smooth_rgb.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../transition/transition.h"
#include "../../types/types.h"
#include <functional>

namespace SmoothUIToolKit
{
    /**
     * @brief A class to represent RGB color with smooth transition.
     * It's actually just Transition3D.
     *
     */
    class SmoothRGB
    {
    public:
        struct Config_t
        {
            std::function<void(SmoothRGB*)> updateCallback = nullptr;
        };

    private:
        struct Data_t
        {
            Transition r_transition;
            Transition g_transition;
            Transition b_transition;
            bool is_changed = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        SmoothRGB() = default;
        SmoothRGB(const int& red, const int& green, const int& blue) { jumpTo(red, green, blue); }

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
        inline void setUpdateCallback(std::function<void(SmoothRGB*)> callback) { _config.updateCallback = callback; }

        inline const int& getCurrentRed() { return _data.r_transition.getValue(); }
        inline const int& getCurrentGreen() { return _data.g_transition.getValue(); }
        inline const int& getCurrentBlue() { return _data.b_transition.getValue(); }

    public:
        /**
         * @brief Jump to target color without transition
         *
         * @param red
         * @param green
         * @param blue
         */
        void jumpTo(const int& red, const int& green, const int& blue);

        /**
         * @brief Move to target color with transition
         *
         * @param red
         * @param green
         * @param blue
         */
        void moveTo(const int& red, const int& green, const int& blue);

        /**
         * @brief Start transition
         *
         * @param currentTime
         */
        void start(const TimeSize_t& currentTime);

        /**
         * @brief Pause transition, call start() to continue
         *
         * @param currentTime
         */
        void pause(const TimeSize_t& currentTime);

        /**
         * @brief End transition to the target color
         *
         */
        void end();

        /**
         * @brief Reset transition to the start color
         *
         */
        void reset();

        /**
         * @brief Update transition
         *
         * @param currentTime
         */
        void update(const TimeSize_t& currentTime);

        /**
         * @brief Is transition finish
         *
         * @return true
         * @return false
         */
        inline bool isFinish()
        {
            return _data.r_transition.isFinish() && _data.g_transition.isFinish() && _data.b_transition.isFinish();
        }
    };
} // namespace SmoothUIToolKit
