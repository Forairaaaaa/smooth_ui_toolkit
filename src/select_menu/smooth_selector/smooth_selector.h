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
                // Camera size
                Vector2D_t cameraSize;
                // Interval of onReadInput() callback
                TimeSize_t readInputInterval = 20;
                // Interval of onRender() callback
                TimeSize_t renderInterval = 15;
            };

        protected:
            struct Data_t
            {
                std::vector<OptionProps_t> option_list;
                Transition2D selector_postion;
                Transition2D selector_shape;
                Transition2D camera_offset;
                int selected_option_index = 0;
                TimeSize_t read_input_time_count = 0;
                TimeSize_t render_time_count = 0;
                bool is_changed = true;
                bool is_pressing = false;
                bool was_released = false;
                bool is_opening = false;
                bool was_opened = false;
            };
            Data_t _data;
            Config_t _config;

        public:
            // Configs
            inline const Config_t& getConfig() { return _config; }
            inline void setConfig(Config_t cfg) { _config = cfg; }
            inline Config_t& setConfig() { return _config; }

            // Options
            inline void addOption(OptionProps_t optionProps) { _data.option_list.push_back(optionProps); }
            inline const std::vector<OptionProps_t>& getOptionList() { return _data.option_list; }
            inline OptionProps_t getSelectedOption() { return _data.option_list[_data.selected_option_index]; }

            // Selector
            inline Transition2D& selectorPostion() { return _data.selector_postion; }
            inline Transition2D& selectorShape() { return _data.selector_shape; }
            inline Vector4D_t getSelectorCurrentFrame()
            {
                return {selectorPostion().getValue().x,
                        selectorPostion().getValue().y,
                        selectorShape().getValue().width,
                        selectorShape().getValue().height};
            }

            // Camera
            inline void setCameraSize(int width, int height)
            {
                _config.cameraSize.width = width;
                _config.cameraSize.height = height;
            }
            inline Transition2D& getCamera() { return _data.camera_offset; }
            inline Vector2D_t getCameraOffset() { return _data.camera_offset.getValue(); }

            /**
             * @brief Select last one
             *
             */
            virtual void goLast();

            /**
             * @brief Select next one
             *
             */
            virtual void goNext();

            /**
             * @brief Press selector to the passing key frame
             *
             * @param pressedKeyframe
             */
            virtual void press(const Vector4D_t& pressedKeyframe);

            /**
             * @brief Is selector being pressed
             *
             * @return true
             * @return false
             */
            inline bool isPressing() { return _data.is_pressing; }

            /**
             * @brief Release selector
             *
             */
            virtual void release();

            /**
             * @brief Open selector to the passing key frame
             *
             * @param pressedKeyframe
             */
            virtual void open(const Vector4D_t& pressedKeyframe);

            /**
             * @brief Is selector opening
             *
             * @return true
             * @return false
             */
            inline const bool& isOpening() { return _data.is_opening; }

            /**
             * @brief Close selector
             *
             */
            virtual void close();

            /**
             * @brief Update menu
             *
             * @param currentTime
             */
            virtual void update(const TimeSize_t& currentTime);

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
