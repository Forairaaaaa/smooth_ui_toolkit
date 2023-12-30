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
     * @brief 1D target with easing path transition 
     * 
     */
    class Smooth1D
    {
    public:
        struct Config_t
        {
            // Transition start 
            int start = 0;

            // Transition end 
            int end = 0;

            // Transition duration (ms)
            std::uint32_t duration = 1000;

            // Duration to wait before transition 
            std::uint32_t delay = 0;

            // Transition path (easing path)
            int (*easing_path)(const int&) = EasingPath::easeOutQuad;

            // Transition update callback 
            void (*update_callback)(Smooth1D* object) = nullptr;
        };

    private:
        struct Data_t
        {
            std::uint32_t start_time = 0;
            int current_value = 0;
            bool is_paused = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        // Transition configs 
        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline void setup(int start, int end, std::uint32_t duration, int (*easingPath)(const int&))
        {
            _config.start = start;
            _config.end = end;
            _config.duration = duration;
            _config.easing_path = easingPath;
        }
        inline void setUpdateCallback(void (*updateCallback)(Smooth1D* object)) { _config.update_callback = updateCallback; }

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
            setup(start, end, duration, easingPath);
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
