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
#include "../easing_path/easing_path.h"
#include "../transition2d/transition2d.h"
#include <functional>

namespace SmoothUIToolKit
{
    /**
     * @brief A class to provide drag and drop offset with transition
     *
     */
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
            EasingPath_t dragTransitionPath = EasingPath::easeOutQuad;

            // Reset transition path when droped
            EasingPath_t resetTransitionPath = EasingPath::easeOutQuad;
        };

    private:
        struct Data_t
        {
            Vector2D_t drag_start_point;
            Vector2D_t drag_start_offset;
            Vector2D_t target_buffer;
            bool is_dragging = false;
            bool is_in_range = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        SmoothDrag() = default;
        SmoothDrag(const int& xStart, const int& yStart) : Transition2D(xStart, yStart) {}
        SmoothDrag(const Vector2D_t& pSatrt) : Transition2D(pSatrt) {}

        // Drag config
        inline Config_t getDragConfig() { return _config; }
        inline Config_t& setDragConfig(void) { return _config; }
        inline void setDragConfig(Config_t cfg) { _config = cfg; }

        // Basic setter
        inline void setTransitionPath(EasingPath_t transitionPath) { _config.dragTransitionPath = transitionPath; }
        inline void setResetTransitionPath(EasingPath_t transitionPath) { _config.resetTransitionPath = transitionPath; }

        /**
         * @brief Start dragging
         *
         * @param x
         * @param y
         */
        void drag(const int& x, const int& y);
        inline void drag(const Vector2D_t& p) { drag(p.x, p.y); }

        /**
         * @brief Stop dragging
         *
         */
        void drop();

        /**
         * @brief Get current drag and drop offset
         *
         * @return Vector2D_t
         */
        inline Vector2D_t getOffset() { return getValue(); }
    };
} // namespace SmoothUIToolKit
