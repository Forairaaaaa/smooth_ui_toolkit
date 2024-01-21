/**
 * @file base.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../core/types/types.h"
#include <vector>

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        /**
         * @brief Provide tree structure and common props.
         *
         */
        class WidgetBase
        {
        protected:
            struct Data_t
            {
                // Parent widget
                WidgetBase* parent = nullptr;

                // Child widgets
                std::vector<WidgetBase*> children;

                // If not, stop invoking onUpdate and onRender (children included)
                bool isEnable = true;

                // If not, stop invoking onRender (children included)
                bool isVisible = true;
            };
            Data_t _data;

        public:
            WidgetBase() = default;
            WidgetBase(WidgetBase* parent) { setParent(parent); }
            virtual ~WidgetBase();

            /**
             * @brief Set parent widget
             *
             * @param parent
             */
            void setParent(WidgetBase* parent);

            /**
             * @brief Get parent widget
             *
             * @return WidgetBase*
             */
            inline WidgetBase* getParent() { return _data.parent; }

            /**
             * @brief Get children widget list
             *
             * @return const std::vector<WidgetBase*>&
             */
            inline const std::vector<WidgetBase*>& getChildren() { return _data.children; }

            /**
             * @brief Is widget's child
             *
             * @param child
             * @return true
             * @return false
             */
            bool isChild(WidgetBase* child);

            /**
             * @brief Add child widget
             *
             * @param child
             */
            void addChild(WidgetBase* child);

            /**
             * @brief Is root widget.
             *
             * @return true
             * @return false
             */
            inline bool isRoot() { return _data.parent == nullptr; }

            /**
             * @brief Is leaf widget
             *
             * @return true
             * @return false
             */
            inline bool isLeaf() { return _data.children.empty(); }

        public:
            /**
             * @brief Set widget's enanle state.
             * If not, onUpdate() and onRender() will stop being invoked (children included).
             *
             * @param enable
             */
            void setEnable(bool isEnable);
            inline bool isEnable() { return _data.isEnable; }

            /**
             * @brief Set widget's visible state.
             * If not, onRender() will stop being invoked (children included).
             *
             * @param isVisible
             */
            void setVisible(bool isVisible);
            inline bool isVisible() { return _data.isVisible; }

        public:
            /**
             * @brief Update widget
             *
             * @param currentTime
             */
            virtual void update(const TimeSize_t& currentTime);

            /**
             * @brief Update child widgets
             *
             * @param currentTime
             */
            virtual void updateChildren(const TimeSize_t& currentTime);

        public:
            virtual void onUpdate(const TimeSize_t& currentTime) {}
            virtual void onRender() {}
        };
    } // namespace Widgets
} // namespace SmoothUIToolKit
