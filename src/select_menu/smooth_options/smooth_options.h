/**
 * @file smooth_options.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/transition2d/transition2d.h"
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <vector>

namespace SmoothUIToolKit
{
    namespace SelectMenu
    {
        /**
         * @brief Menu with smooth options
         * Option moves looply in keyframe list, means keyframe num equals to the option num
         * The option at the first keyframe currently treated as the selected one
         *
         */
        class SmoothOptions
        {
        public:
            /**
             * @brief Option properties
             *
             */
            struct OptionProps_t
            {
                Transition2D position;
                Transition2D shape;
                void* userData = nullptr;
            };

            struct Config_t
            {
                // Interval of onReadInput() callback
                TimeSize_t readInputInterval = 20;
                // Interval of onRender() callback
                TimeSize_t renderInterval = 15;
            };

        protected:
            struct Data_t
            {
                std::vector<OptionProps_t> option_list;
                std::vector<Vector4D_t> keyframe_list;
                bool is_changed = true;
                int selected_option_index = 0;
                TimeSize_t read_input_time_count = 0;
                TimeSize_t render_time_count = 0;
            };
            Data_t _data;
            Config_t _config;
            void _update_option_keyframe();
            void _invoke_option_update(const TimeSize_t& currentTime);

        public:
            // Config
            inline const Config_t getConfig() { return _config; }
            inline void setConfig(Config_t cfg) { _config = cfg; }
            inline Config_t& setConfig() { return _config; }

            // Keyframe
            inline const std::vector<Vector4D_t>& getKeyframeList() { return _data.keyframe_list; }
            inline const Vector4D_t& getKeyframe(const int& index) { return _data.keyframe_list[index]; }
            inline void setKeyframe(int index, Vector4D_t keyframe) { _data.keyframe_list[index] = keyframe; }
            inline Vector4D_t& setKeyframe(int index) { return _data.keyframe_list[index]; }
            inline void setLastKeyframe(Vector4D_t keyframe) { _data.keyframe_list.back() = keyframe; }

            // Options
            inline const std::vector<OptionProps_t>& getOptionList() { return _data.option_list; }
            inline OptionProps_t& getOption(const int& index) { return _data.option_list[index]; }
            inline OptionProps_t& setOption(int index) { return _data.option_list[index]; }
            inline Vector4D_t getOptionCurrentFrame(const int& index)
            {
                return {getOption(index).position.getValue().x, getOption(index).position.getValue().y,
                        getOption(index).shape.getValue().width, getOption(index).shape.getValue().height};
            }

            /**
             * @brief Set the position transition duration to all options
             *
             * @param duration
             */
            void setPositionDuration(TimeSize_t duration);

            /**
             * @brief Set the shape transition duration to all optionos
             *
             * @param duration
             */
            void setShapeDuration(TimeSize_t duration);

            /**
             * @brief Set the postion transition path to all optionos
             *
             * @param path
             */
            void setPositionTransitionPath(EasingPathPtr path);

            /**
             * @brief Set the shape transition path to all optionos
             *
             * @param path
             */
            void setShapeTransitionPath(EasingPathPtr path);

            inline void setDuration(TimeSize_t duration)
            {
                setPositionDuration(duration);
                setShapeDuration(duration);
            }

            inline void setTransitionPath(EasingPathPtr path)
            {
                setPositionTransitionPath(path);
                setShapeTransitionPath(path);
            }

            /**
             * @brief Add option into menu
             *
             * @param userData
             */
            void addOption(void* userData = nullptr);

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
             * @brief Update the selected option with pressed key frame
             *
             * @param pressedKeyframe
             */
            virtual void press(const Vector4D_t& pressedKeyframe);

            /**
             * @brief Release the selected option
             *
             */
            virtual void release();

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
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onReadInput() {}
            virtual void onRender() {}

        public:
            /**
             * @brief Get the option index that the keyframe is currently matching
             * This can be used to render props in keyframe order
             *
             * @param keyframeIndex
             * @param matchedOptionIndex
             */
            void getMatchingOptionIndex(const int& keyframeIndex, int& matchedOptionIndex);
        };
    } // namespace SelectMenu
} // namespace SmoothUIToolKit