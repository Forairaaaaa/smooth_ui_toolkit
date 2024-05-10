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
#include "../easing_path/easing_path.h"
#include "../transition/transition.h"
#include "../types/types.h"
#include <functional>

namespace SmoothUIToolKit
{
    /**
     * @brief A container of 2 Transitions, provides dynamic transition methods
     *
     */
    class Transition2D
    {
    public:
        struct Config_t
        {
            std::function<void(Transition2D*)> updateCallback = nullptr;
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
        Transition2D(const Vector2D_t& pSatrt) { jumpTo(pSatrt); }

        // Basic setter
        inline void setDuration(TimeSize_t duration)
        {
            _data.x_transition.setDuration(duration);
            _data.y_transition.setDuration(duration);
        }
        inline void setDelay(TimeSize_t delay)
        {
            _data.x_transition.setDelay(delay);
            _data.y_transition.setDelay(delay);
        }
        inline void setTransitionPath(EasingPath_t transitionPath)
        {
            _data.x_transition.setTransitionPath(transitionPath);
            _data.y_transition.setTransitionPath(transitionPath);
        }
        inline void setUpdateCallback(std::function<void(Transition2D*)> updateCallback)
        {
            _config.updateCallback = updateCallback;
        }

        // Basic getter
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }
        inline Vector2D_t getStartPoint()
        {
            return Vector2D_t(_data.x_transition.getStartValue(), _data.y_transition.getStartValue());
        }
        inline Vector2D_t getTargetPoint()
        {
            return Vector2D_t(_data.x_transition.getEndValue(), _data.y_transition.getEndValue());
        }
        inline std::function<void(Transition2D*)> getUpdateCallback() { return _config.updateCallback; }

        // Helper setter
        inline void setEachDuration(TimeSize_t x, TimeSize_t y)
        {
            _data.x_transition.setDuration(x);
            _data.y_transition.setDuration(y);
        }
        inline void setEachDelay(TimeSize_t x, TimeSize_t y)
        {
            _data.x_transition.setDelay(x);
            _data.y_transition.setDelay(y);
        }
        inline void setEachTransitionPath(EasingPath_t x, EasingPath_t y)
        {
            _data.x_transition.setTransitionPath(x);
            _data.y_transition.setTransitionPath(y);
        }

        /**
         * @brief Start moving
         *
         * @param currentTime
         */
        void start(const TimeSize_t& currentTime);

        /**
         * @brief Pause moving, call start() to continue
         *
         * @param currentTime
         */
        void pause(const TimeSize_t& currentTime);

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
        void update(const TimeSize_t& currentTime);

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

        /** Resize to target size with no transition
         * @brief
         *
         * @param w
         * @param h
         */
        inline void resizeTo(const int& w, const int& h) { jumpTo(w, h); }
        inline void resizeTo(const Vector2D_t& p) { jumpTo(p); }

        /** Reshape to target size smoothly
         * @brief
         *
         * @param w
         * @param h
         */
        inline void reshapeTo(const int& w, const int& h) { moveTo(w, h); }
        inline void reshapeTo(const Vector2D_t& p) { moveTo(p); }

        /**
         * @brief Get current point
         *
         * @return Vector2D_t
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
} // namespace SmoothUIToolKit
