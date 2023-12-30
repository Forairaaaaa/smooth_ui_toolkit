/**
 * @file smooth_point.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../types/types.h"
#include "../transition/transition.h"
#include "core/easing_path/easing_path.h"


namespace SmoothUIToolKit
{
    class SmoothPoint;
    typedef void (*SmoothPointUpdateCallbackPtr)(SmoothPoint*);

    class SmoothPoint
    {
    public:
        struct Config_t
        {
            SmoothPointUpdateCallbackPtr updateCallback = nullptr;
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
        SmoothPoint() = default;
        SmoothPoint(const int& xStart, const int& yStart) { jumpTo(xStart, yStart); }
        SmoothPoint(const Vector2D_t& pSatrt) { jumpTo(pSatrt); }

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
        inline void setUpdateCallback(SmoothPointUpdateCallbackPtr updateCallback)
        {
            _config.updateCallback = updateCallback;
        }

        // Basic getter 
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }
        inline Vector2D_t getStartPoint() { return Vector2D_t(_data.x_transition.getStartValue(), _data.y_transition.getStartValue()); }
        inline Vector2D_t getTargetPoint() { return Vector2D_t(_data.x_transition.getEndValue(), _data.y_transition.getEndValue()); }
        inline SmoothPointUpdateCallbackPtr getUpdateCallback() { return _config.updateCallback; }

        /**
         * @brief Start moving  
         * 
         * @param currentTime 
         */
        void start(const std::uint32_t& currentTime);

        /**
         * @brief Pause moving, call start() to continue 
         * 
         */
        void pause();

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
        inline void jumpTo(const Vector2D_t& p) { jumpTo(p.x, p.y); }

        /**
         * @brief Move to target point smoothly 
         * 
         * @param x 
         * @param y 
         * @param currentTime 
         */
        void moveTo(const int& x, const int& y);
        inline void moveTo(const Vector2D_t& p) { moveTo(p.x, p.y); }

        /**
         * @brief Get current point  
         * 
         * @return int 
         */
        inline Vector2D_t getValue() { return Vector2D_t(_data.x_transition.getValue(), _data.y_transition.getValue()); }

        /**
         * @brief Is moving finish 
         * 
         * @return true 
         * @return false 
         */
        inline bool isFinish() { return _data.x_transition.isFinish() && _data.y_transition.isFinish(); }
    };
}
