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
#include "../types/types.h"
#include "../easing_path/easing_path.h"
#include <cstdint>
// Refs:
// https://developer.mozilla.org/en-US/docs/Web/CSS/transition


namespace SmoothUIToolKit
{
    class Transition;
    typedef void (*TransitionUpdateCallbackPtr)(Transition*);

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
            std::uint32_t duration = 1000;

            // Duration to wait before transition 
            std::uint32_t delay = 0;

            // Transition path (easing path)
            int (*transitionPath)(const int&) = EasingPath::easeOutQuad;

            // Transition update callback 
            void (*updateCallback)(Transition*) = nullptr;

            void* userData = nullptr;
        };

    private:
        struct Data_t
        {
            std::uint32_t time_offset = 0;
            int current_value = 0;
            bool is_paused = true;
            bool is_finish = false;
        };
        Data_t _data;
        Config_t _config;
        void _update_value(const std::uint32_t& currentTime);

    public:
        Transition() = default;
        Transition(Config_t cfg) { _config = cfg; }
        Transition(int start, int end, std::uint32_t duration, int (*easingPath)(const int&)) { setConfig(start, end, duration, easingPath); }

        // Transition configs 
        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline void setConfig(int start, int end)
        {
            _config.startValue = start;
            _config.endValue = end;
        }
        inline void setConfig(int start, int end, std::uint32_t duration, int (*easingPath)(const int&))
        {
            setConfig(start, end);
            _config.duration = duration;
            _config.transitionPath = easingPath;
        }
        
        // Basic setter 
        inline void setStartValue(int startValue) { _config.startValue = startValue; }
        inline void setEndValue(int endValue) { _config.endValue = endValue; }
        inline void setDuration(std::uint32_t duration) { _config.duration = duration; }
        inline void setDelay(std::uint32_t delay) { _config.delay = delay; }
        inline void setTransitionPath(int (*transitionPath)(const int&)) { _config.transitionPath = transitionPath; }
        inline void setUpdateCallback(void (*updateCallback)(Transition* object)) { _config.updateCallback = updateCallback; }
        inline void setUserData(void* userData) { _config.userData = userData; }

        // Basic getter 
        inline int getStartValue() { return _config.startValue; }
        inline int getEndValue() { return _config.endValue; }
        inline std::uint32_t getDuration() { return _config.duration; }
        inline std::uint32_t getDelay() { return _config.delay; }
        inline EasingPathPtr getTransitionPath() { return _config.transitionPath; }
        inline TransitionUpdateCallbackPtr getUpdateCallback() { return _config.updateCallback; }
        inline void* getUserData() { return _config.userData; }

        /**
         * @brief Start transition 
         * 
         * @param currentTime 
         */
        void start(std::uint32_t currentTime);

        /**
         * @brief Pause transition, call start() to continue 
         * 
         */
        void pause();

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
        void update(std::uint32_t currentTime);

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
}
