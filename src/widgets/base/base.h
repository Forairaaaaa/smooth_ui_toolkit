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
#include <functional>
#include <vector>

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        /**
         * @brief Provide tree structure and common widget logic callbacks for animation
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

                // Auto invoke render() after root widget update
                bool renderOnUpdate = true;

                // Poped out or retracting
                bool isWidgetRetracting = true;
            };
            Data_t _base_data;

        public:
            WidgetBase() = default;
            WidgetBase(WidgetBase* parent) { setParent(parent); }
            virtual ~WidgetBase();

            /* -------------------------------------------------------------------------- */
            /*                                 Widget tree                                */
            /* -------------------------------------------------------------------------- */
        public:
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
            inline WidgetBase* getParent() { return _base_data.parent; }

            /**
             * @brief Get children widget list
             *
             * @return const std::vector<WidgetBase*>&
             */
            inline const std::vector<WidgetBase*>& getChildren() { return _base_data.children; }

            /**
             * @brief Helper method to iterate every child
             *
             * @param callback
             */
            void iterateChildren(std::function<void(WidgetBase* child)> callback);

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
            inline bool isRoot() { return _base_data.parent == nullptr; }

            /**
             * @brief Is leaf widget
             *
             * @return true
             * @return false
             */
            inline bool isLeaf() { return _base_data.children.empty(); }

            /* -------------------------------------------------------------------------- */
            /*                                   Status                                   */
            /* -------------------------------------------------------------------------- */
        public:
            /**
             * @brief Set widget's enanle state.
             * If not, onUpdate() and onRender() will stop being invoked (children included).
             *
             * @param enable
             */
            inline void setEnable(bool isEnable) { _base_data.isEnable = isEnable; }
            inline bool isEnable() { return _base_data.isEnable; }

            /**
             * @brief Set widget's visible state.
             * If not, onRender() will stop being invoked (children included).
             *
             * @param isVisible
             */
            inline void setVisible(bool isVisible) { _base_data.isVisible = isVisible; }
            inline bool isVisible() { return _base_data.isVisible; }

            /**
             * @brief Is popup or any anim is finished
             *
             * @return true
             * @return false
             */
            virtual bool isAnimFinish() { return true; }

            /**
             * @brief Is widget completely retracting
             *
             * @return true
             * @return false
             */
            virtual bool isRetracting();

            /**
             * @brief Is widget completely popped out
             *
             * @return true
             * @return false
             */
            virtual bool isPoppedOut();

            /* -------------------------------------------------------------------------- */
            /*                                   Update                                   */
            /* -------------------------------------------------------------------------- */
        public:
            /**
             * @brief Update widget
             *
             */
            virtual void update();

            /* -------------------------------------------------------------------------- */
            /*                                   Render                                   */
            /* -------------------------------------------------------------------------- */
        public:
            /**
             * @brief Render widget
             *
             */
            virtual void render();

            /* -------------------------------------------------------------------------- */
            /*                               Common methods                               */
            /* -------------------------------------------------------------------------- */
            // Children methods will also be invoked
        public:
            /**
             * @brief Init your shit
             *
             */
            virtual void init();

            /**
             * @brief Reset widget
             *
             */
            virtual void reset();

            /**
             * @brief Set your pop out anim maybe
             *
             */
            virtual void popOut();

            /**
             * @brief Set your retract anim maybe
             *
             */
            virtual void retract();

            /* -------------------------------------------------------------------------- */
            /*                                  Callbacks                                 */
            /* -------------------------------------------------------------------------- */
        public:
            virtual void onInit() {}
            virtual void onReset() {}
            virtual void onPopOut() {}
            virtual void onRetract() {}
            virtual void onUpdate() {}
            virtual void onRender() {}
            virtual void onPostRender() {}
        };
    } // namespace Widgets
} // namespace SmoothUIToolKit
