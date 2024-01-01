/**
 * @file smooth_drag.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../transition2d/transition2d.h"
#include "core/easing_path/easing_path.h"


namespace SmoothUIToolKit
{
    /**
     * @brief A class to provide drag and drop offset with transition 
     * 
     */
    class SmoothDrag;

    typedef void (*SmoothDragUpdateCallbackPtr)(SmoothDrag*);

    class SmoothDrag : public Transition2D
    {
    public:
        struct Config_t
        {
            // Lock x offset 
            bool lockXOffset = false;

            // Lock y offset 
            bool lockYOffset = false;

            // Auto reset offset when droped 
            bool autoReset = false;

            // Limit offset 
            bool offsetLimit = false;

            // bool sss = true;
            bool allowDraggingOutOfLimit = true;

            // X offset limit 
            Vector2D_t xOffsetLimit;

            // Y offset limit 
            Vector2D_t yOffsetLimit;

            // Drag transition path 
            EasingPathPtr dragTransitionPath = EasingPath::easeOutQuad;

            // Reset transition path when droped 
            EasingPathPtr resetTransitionPath = EasingPath::easeOutQuad;
        };

    private:
        struct Data_t
        {
            Point_t drag_start_point;
            Point_t drag_start_offset;
            Point_t target_buffer;
            bool is_dragging = false;
            bool is_in_range = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        SmoothDrag() = default;
        SmoothDrag(const int& xStart, const int& yStart) : Transition2D(xStart, yStart) {}
        SmoothDrag(const Point_t& pSatrt) : Transition2D(pSatrt) {}

        // Drag config
        inline Config_t getDragConfig() { return _config; }
        inline Config_t& setDragConfig(void) { return _config; }
        inline void setDragConfig(Config_t cfg) { _config = cfg; }

        // Basic setter 
        inline void setTransitionPath(EasingPathPtr transitionPath) { _config.dragTransitionPath = transitionPath; }
        inline void setResetTransitionPath(EasingPathPtr transitionPath) { _config.resetTransitionPath = transitionPath; }
        inline void setUpdateCallback(SmoothDragUpdateCallbackPtr updateCallback)
        {
            Transition2D::setUpdateCallback(reinterpret_cast<Transition2DUpdateCallbackPtr>(updateCallback));
        }

        /**
         * @brief Start dragging 
         * 
         * @param x 
         * @param y 
         */
        void drag(const int& x, const int& y);
        inline void drag(const Point_t& p) { drag(p.x, p.y); }

        /**
         * @brief Stop dragging 
         * 
         */
        void drop();

        /**
         * @brief Get current drag and drop offset 
         * 
         * @return Point_t 
         */
        inline Point_t getOffset() { return getValue(); }
    };
}

