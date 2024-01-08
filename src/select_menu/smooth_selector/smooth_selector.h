/**
 * @file smooth_selector.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/transition2d/transition2d.h"
#include <cstdint>
#include <vector>

namespace SmoothUIToolKit
{
    namespace SelectMenu
    {
        /**
         * @brief Menu with a smooth selector.
         * Selector moves to match the option keyframes.
         * The option matched by the selector at that time, treated as the selected one.
         * Camera provides smooth offset to keep selector inside.
         * Handy for list menu with a moving selector,
         * or moving options with simple postition and shape transition. (Use selector as coordinate origin)
         */
        class SmoothSelector
        {
        public:
            /**
             * @brief Option properties
             *
             */
            struct OptionProps_t
            {
                Vector4D_t keyframe;
                void* userData = nullptr;
            };

            struct Config_t
            {
                // Selector move in loop
                bool moveInLoop = true;
                
                Vector2D_t cameraSize;
            };

        private:
            struct Data_t
            {
                std::vector<OptionProps_t> option_list;
                Transition2D selector_postion;
                Transition2D selector_shape;
                Transition2D camera_offset;
            };
            Data_t _data;
            Config_t _config;

        public:
            // Configs
            inline const Config_t& getConfig() { return _config; }
            inline void setConfig(Config_t cfg) { _config = cfg; }
            inline Config_t& setConfig() { return _config; }

            // Camera 
            inline Transition2D& getCamera() { return _data.camera_offset; }
            inline Vector2D_t getCameraOffset() { return _data.camera_offset.getValue(); }


        };
    } // namespace SelectMenu
} // namespace SmoothUIToolKit
