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
            struct OptionProps_t
            {
                Transition2D position;
                Transition2D shape;
                void* userData = nullptr;
            };

            struct Keyframe_t
            {
                Vector2D_t position;
                Vector2D_t shape;
            };

        protected:
            struct Data_t
            {
                std::vector<OptionProps_t> option_list;
                std::vector<Keyframe_t> keyframe_list;
                bool is_changed = true;
                int selected_option_index = 0;
            };
            Data_t _data;
            void _update_option_keyframe();
            void _invoke_option_update(const TimeSize_t& currentTime);

        public:
            inline const std::vector<Keyframe_t>& getKeyframeList() { return _data.keyframe_list; }
            inline const std::vector<OptionProps_t>& getOptionList() { return _data.option_list; }

            /**
             * @brief Set keyframe
             *
             * @param index
             * @return Keyframe_t&
             */
            inline Keyframe_t& setKeyframe(int index) { return _data.keyframe_list[index]; }

            /**
             * @brief Set option properties
             *
             * @param index
             * @return OptionProps_t&
             */
            inline OptionProps_t& setOption(int index) { return _data.option_list[index]; }

            /**
             * @brief Add option into menu
             *
             * @param userData
             */
            void addOption(void* userData);

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
            virtual void press(const Keyframe_t& pressedKeyframe);

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
