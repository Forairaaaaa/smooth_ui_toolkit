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
    namespace SmoothWidget 
    {
        class WidgetBase
        {
        protected:
            // x, y
            Vector2D_t _position;
            // w, h
            Vector2D_t _size;
            // Parent widget 
            WidgetBase* _parent = nullptr;
            // Child widgets 
            std::vector<WidgetBase*> _children;

        public:
            WidgetBase() = default;
            WidgetBase(int x, int y, int width, int height)
            {
                setPostion(x, y);
                setSize(width, height);
            }
            WidgetBase(Vector2D_t position, Vector2D_t size)
            {
                _position = position;
                _size = size;
            }

            // Basic getter 
            inline const Vector2D_t& getPostion() { return _position; }
            inline const Vector2D_t& getSize() { return _size; }

            // Basic setter 
            inline void setPostion(int x, int y) { _position.reset(x, y); }
            inline Vector2D_t& setPostion() { return _position; }
            inline void setSize(int width, int height) { _size.reset(width, height); }
            inline Vector2D_t& setSize() { return _size; }
            
            // Widget tree apis 
            inline void setParent(WidgetBase* parent) { _parent = parent; }
            inline WidgetBase* getParent() { return _parent; }
            inline const std::vector<WidgetBase*>& getChildren() { return _children; }
            bool isChild(WidgetBase* child);
            void addChild(WidgetBase* child);
    
            /**
             * @brief Tell widget what time is it and update 
             * 
             * @param currentTime 
             */
            virtual void update(const std::uint32_t& currentTime);

            /**
             * @brief Tell widget where the cursor is now 
             * 
             * @param x 
             * @param y 
             */
            virtual void hover(const int& x, const int& y);

            /**
             * @brief Tell widget where the pressing cursor is now 
             * 
             * @param x 
             * @param y 
             */
            virtual void drag(const int& x, const int& y);

            /**
             * @brief Tell widget cursor just released 
             * 
             */
            virtual void drop();

            /**
             * @brief Callback when every update 
             * 
             * @param currentTime 
             */
            virtual void onUpdate(const std::uint32_t& currentTime) {}
            
            /**
             * @brief Callback when cursor start hovering on widget 
             * 
             */
            virtual void onHover() {}

            /**
             * @brief Callback when cursor hovering on widget 
             * 
             * @param x 
             * @param y 
             */
            virtual void onHovering(const int& x, const int& y) {}

            /**
             * @brief Callback when cursor leave the widget 
             * 
             */
            virtual void onHoverEnd() {}

            /**
             * @brief Callback when cursor start dragging on widget 
             * 
             */
            virtual void onDrag() {}

            /**
             * @brief Callback when cursor is dragging on widget 
             * 
             * @param x 
             * @param y 
             */
            virtual void onDragging(const int& x, const int& y) {}

            /**
             * @brief Callback when cursor droped from widget 
             * 
             */
            virtual void onDrop() {}
        
        private:
            struct Data_t
            {
                bool is_hovering = false;
                bool is_dragging = false;
            };
            Data_t _data;
            
            bool _is_on_widget(const int& x, const int& y);
            void _invoke_children_update(const std::uint32_t& currentTime);
            void _invoke_children_hover(const int& x, const int& y);
            void _invoke_children_drag(const int& x, const int& y);
            void _invoke_children_drop();
        };
    }
}
