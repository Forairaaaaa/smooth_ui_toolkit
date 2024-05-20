/**
 * @file transition.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "../easing_path/easing_path.h"
#include "../types/types.h"
#include <cstdint>
#include <functional>
// Refs:
// https://developer.mozilla.org/en-US/docs/Web/CSS/transition

namespace SmoothUIToolKit
{
    /**
     * @brief Transition in esing path
     *
     */
    class Transition
    {
    public:
        struct Config_t
        {
            // Transition start
            int startValue = 0;

            // Transition end
            int endValue = 0;

            // Transition duration (ms)
            TimeSize_t duration = 1000;

            // Duration to wait before transition
            TimeSize_t delay = 0;

            // Transition path (easing path)
            EasingPath_t transitionPath = EasingPath::easeOutQuad;

            // Transition update callback
            std::function<void(Transition*)> updateCallback = nullptr;

            void* userData = nullptr;
        };

    private:
        struct Data_t
        {
            TimeSize_t time_offset = 0;
            TimeSize_t pause_time = 0;
            TimeSize_t pause_offset = 0;
            int current_value = 0;
            bool is_paused = true;
            bool is_finish = true;
        };
        Data_t _data;
        Config_t _config;
        void _update_value(const TimeSize_t& currentTime);

    public:
        Transition() = default;
        Transition(Config_t cfg) { _config = cfg; }
        Transition(int start, int end, TimeSize_t duration, EasingPath_t transitionPath)
        {
            setConfig(start, end, duration, transitionPath);
        }

        // Transition configs
        inline Config_t getConfig() { return _config; }
        inline Config_t& setConfig(void) { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline void setConfig(int start, int end)
        {
            _config.startValue = start;
            _config.endValue = end;
        }
        inline void setConfig(int start, int end, TimeSize_t duration, EasingPath_t transitionPath)
        {
            setConfig(start, end);
            _config.duration = duration;
            _config.transitionPath = transitionPath;
        }

        // Basic setter
        inline void setStartValue(int startValue) { _config.startValue = startValue; }
        inline void setEndValue(int endValue) { _config.endValue = endValue; }
        inline void setDuration(TimeSize_t duration) { _config.duration = duration; }
        inline void setDelay(TimeSize_t delay) { _config.delay = delay; }
        inline void setTransitionPath(EasingPath_t transitionPath) { _config.transitionPath = transitionPath; }
        inline void setUpdateCallback(std::function<void(Transition*)> updateCallback)
        {
            _config.updateCallback = updateCallback;
        }
        inline void setUserData(void* userData) { _config.userData = userData; }

        // Basic getter
        inline int getStartValue() { return _config.startValue; }
        inline int getEndValue() { return _config.endValue; }
        inline TimeSize_t getDuration() { return _config.duration; }
        inline TimeSize_t getDelay() { return _config.delay; }
        inline EasingPath_t getTransitionPath() { return _config.transitionPath; }
        inline std::function<void(Transition*)> getUpdateCallback() { return _config.updateCallback; }
        inline void* getUserData() { return _config.userData; }

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
         * @brief End transition to the end
         *
         */
        void end();

        /**
         * @brief Reset tansition to the start
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
         * @brief Get transtion's current value
         *
         * @return int
         */
        inline const int& getValue() { return _data.current_value; }

        /**
         * @brief Is transition finish
         *
         * @return true
         * @return false
         */
        inline bool isFinish() { return _data.is_finish; }
    };
} // namespace SmoothUIToolKit
