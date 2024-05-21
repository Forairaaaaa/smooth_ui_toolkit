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
         * @brief Provide tree structure, basic status, methods and callbacks
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
                bool is_enable = true;

                // If not, stop invoking onRender (children included)
                bool is_visible = true;

                // Auto invoke render() after root widget update
                bool render_on_update = true;
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

        public:
            /**
             * @brief Set widget's enanle state.
             * If not, onUpdate() and onRender() will stop being invoked (children included).
             *
             * @param enable
             */
            inline void setEnable(bool isEnable) { _base_data.is_enable = isEnable; }
            inline bool isEnable() { return _base_data.is_enable; }

            /**
             * @brief Set widget's visible state.
             * If not, onRender() will stop being invoked (children included).
             *
             * @param isVisible
             */
            inline void setVisible(bool isVisible) { _base_data.is_visible = isVisible; }
            inline bool isVisible() { return _base_data.is_visible; }

            /**
             * @brief Set auto invoke render() after root widget update
             *
             * @param renderOnUpdate
             */
            inline void setRenderOnUpdate(bool renderOnUpdate) { _base_data.render_on_update = renderOnUpdate; }
            inline bool getRenderOnUpdate() { return _base_data.render_on_update; }

            /**
             * @brief Init your shit
             *
             */
            virtual void init();

            /**
             * @brief Update widget
             *
             */
            virtual void update(void);

            /**
             * @brief Render widget
             *
             */
            virtual void render();

            /**
             * @brief Reset widget
             *
             */
            virtual void reset();

            /* -------------------------------------------------------------------------- */
            /*                                  Callbacks                                 */
            /* -------------------------------------------------------------------------- */
        public:
            virtual void onInit() {}
            virtual void onReset() {}
            virtual void onUpdate() {}
            virtual void onRender() {}
            virtual void onPostRender() {}
        };
    } // namespace Widgets
} // namespace SmoothUIToolKit
