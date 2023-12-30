/**
 * @file smooth1d.h
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
            int (*easingPath)(const int&) = EasingPath::easeOutQuad;

            // Transition update callback 
            void (*updateCallback)(Transition* object) = nullptr;
        };

    private:
        struct Data_t
        {
            std::uint32_t time_offset = 0;
            int current_value = 0;
            bool is_paused = true;
            bool is_finished = false;
        };
        Data_t _data;
        Config_t _config;

    public:
        // Transition configs 
        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline void setConfig(int start, int end, std::uint32_t duration, int (*easingPath)(const int&))
        {
            _config.startValue = start;
            _config.endValue = end;
            _config.duration = duration;
            _config.easingPath = easingPath;
        }
        inline void setUpdateCallback(void (*updateCallback)(Transition* object)) { _config.updateCallback = updateCallback; }

        /**
         * @brief Start transition 
         * 
         * @param currentTime 
         */
        void start(std::uint32_t currentTime);

        /**
         * @brief Pasue transition, call start() to continue 
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
         * @brief Reset tansition to the start with new config 
         * 
         */
        inline void reset(int start, int end, std::uint32_t duration, int (*easingPath)(const int&))
        {
            setConfig(start, end, duration, easingPath);
            reset();
        }
        
        /**
         * @brief Update transition 
         * 
         * @param currentTime 
         */
        void update(std::uint32_t currentTime);

        /**
         * @brief Get current value 
         * 
         * @return int 
         */
        inline int getValue() { return _data.current_value; }
    };
}
