/**
 * @file transition2d.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-12-31
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include "../transition/transition.h"
#include "../types/types.h"
#include "core/easing_path/easing_path.h"

namespace SmoothUIToolKit
{
    // Callback define
    class Transition2D;
    typedef void (*Transition2DUpdateCallbackPtr)(Transition2D*);

    /**
     * @brief A container of 2 Transition, provides dynamic transition methods
     *
     */
    class Transition2D
    {
    public:
        struct Config_t
        {
            Transition2DUpdateCallbackPtr updateCallback = nullptr;
        };

    private:
        struct Data_t
        {
            Transition x_transition;
            Transition y_transition;
            bool is_changed = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        Transition2D() = default;
        Transition2D(const int& xStart, const int& yStart) { jumpTo(xStart, yStart); }
        Transition2D(const Point_t& pSatrt) { jumpTo(pSatrt); }

        // Basic setter
        inline void setDuration(std::uint32_t duration)
        {
            _data.x_transition.setDuration(duration);
            _data.y_transition.setDuration(duration);
        }
        inline void setDelay(std::uint32_t delay)
        {
            _data.x_transition.setDelay(delay);
            _data.y_transition.setDelay(delay);
        }
        inline void setTransitionPath(EasingPathPtr transitionPath)
        {
            _data.x_transition.setTransitionPath(transitionPath);
            _data.y_transition.setTransitionPath(transitionPath);
        }
        inline void setUpdateCallback(Transition2DUpdateCallbackPtr updateCallback) { _config.updateCallback = updateCallback; }

        // Basic getter
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }
        inline Point_t getStartPoint()
        {
            return Point_t(_data.x_transition.getStartValue(), _data.y_transition.getStartValue());
        }
        inline Point_t getTargetPoint() { return Point_t(_data.x_transition.getEndValue(), _data.y_transition.getEndValue()); }
        inline Transition2DUpdateCallbackPtr getUpdateCallback() { return _config.updateCallback; }

        /**
         * @brief Start moving
         *
         * @param currentTime
         */
        void start(const std::uint32_t& currentTime);

        /**
         * @brief Pause moving, call start() to continue
         *
         * @param currentTime
         */
        void pause(const std::uint32_t& currentTime);

        /**
         * @brief End moving to the target point
         *
         */
        void end();

        /**
         * @brief Reset moving to the start point
         *
         */
        void reset();

        /**
         * @brief Update moving
         *
         * @param currentTime
         */
        void update(const std::uint32_t& currentTime);

        /**
         * @brief Jump to target point with no transition
         *
         * @param x
         * @param y
         */
        void jumpTo(const int& x, const int& y);
        inline void jumpTo(const Point_t& p) { jumpTo(p.x, p.y); }

        /**
         * @brief Move to target point smoothly
         *
         * @param x
         * @param y
         * @param currentTime
         */
        void moveTo(const int& x, const int& y);
        inline void moveTo(const Point_t& p) { moveTo(p.x, p.y); }

        /** Resize to target size with no transition
         * @brief
         *
         * @param w
         * @param h
         */
        inline void resizeTo(const int& w, const int& h) { jumpTo(w, h); }
        inline void resizeTo(const Point_t& p) { jumpTo(p); }

        /** Reshape to target size smoothly
         * @brief
         *
         * @param w
         * @param h
         */
        inline void reshapeTo(const int& w, const int& h) { moveTo(w, h); }
        inline void reshapeTo(const Point_t& p) { moveTo(p); }

        /**
         * @brief Get current point
         *
         * @return int
         */
        inline Point_t getValue() { return Point_t(_data.x_transition.getValue(), _data.y_transition.getValue()); }

        /**
         * @brief Is moving finish
         *
         * @return true
         * @return false
         */
        inline bool isFinish() { return _data.x_transition.isFinish() && _data.y_transition.isFinish(); }
    };
} // namespace SmoothUIToolKit
