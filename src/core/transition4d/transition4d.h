/**
 * @file transition4d.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../transition/transition.h"
#include "../types/types.h"
#include <functional>

namespace SmoothUIToolKit
{
    /**
     * @brief A container of 4 Transitions, provides dynamic transition methods
     *
     */
    class Transition4D
    {
    public:
        struct Config_t
        {
            std::function<void(Transition4D*)> updateCallback = nullptr;
        };

    private:
        struct Data_t
        {
            Transition x_transition;
            Transition y_transition;
            Transition w_transition;
            Transition h_transition;
            bool is_changed = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        Transition4D() = default;
        Transition4D(const int& xStart, const int& yStart, const int& wStart, const int& hStart)
        {
            jumpTo(xStart, yStart, wStart, hStart);
        }
        Transition4D(const Vector4D_t& pSatrt) { jumpTo(pSatrt); }

        // Basic setter
        inline void setDuration(TimeSize_t duration)
        {
            _data.x_transition.setDuration(duration);
            _data.y_transition.setDuration(duration);
            _data.w_transition.setDuration(duration);
            _data.h_transition.setDuration(duration);
        }
        inline void setDelay(TimeSize_t delay)
        {
            _data.x_transition.setDelay(delay);
            _data.y_transition.setDelay(delay);
            _data.w_transition.setDelay(delay);
            _data.h_transition.setDelay(delay);
        }
        inline void setTransitionPath(EasingPathPtr transitionPath)
        {
            _data.x_transition.setTransitionPath(transitionPath);
            _data.y_transition.setTransitionPath(transitionPath);
            _data.w_transition.setTransitionPath(transitionPath);
            _data.h_transition.setTransitionPath(transitionPath);
        }
        inline void setUpdateCallback(std::function<void(Transition4D*)> callback) { _config.updateCallback = callback; }

        // Basic getter
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }
        inline Transition& getWTransition() { return _data.w_transition; }
        inline Transition& getHTransition() { return _data.h_transition; }
        inline Vector4D_t getStartPoint()
        {
            return Vector4D_t(_data.x_transition.getStartValue(),
                              _data.y_transition.getStartValue(),
                              _data.w_transition.getStartValue(),
                              _data.h_transition.getStartValue());
        }
        inline Vector4D_t getTargetPoint()
        {
            return Vector4D_t(_data.x_transition.getEndValue(),
                              _data.y_transition.getEndValue(),
                              _data.w_transition.getEndValue(),
                              _data.h_transition.getEndValue());
        }

    public:
        /**
         * @brief Jump to target point without transition
         *
         * @param x
         * @param y
         * @param w
         * @param h
         */
        void jumpTo(const int& x, const int& y, const int& w, const int& h);
        inline void jumpTo(const Vector4D_t& p) { jumpTo(p.x, p.y, p.w, p.h); }

        /**
         * @brief Move to target point with transition
         *
         * @param x
         * @param y
         * @param w
         * @param h
         */
        void moveTo(const int& x, const int& y, const int& w, const int& h);
        inline void moveTo(const Vector4D_t& p) { moveTo(p.x, p.y, p.w, p.h); }

        /**
         * @brief Start transition
         *
         * @param currentTime
         */
        void start(const TimeSize_t& currentTime);

        /**
         * @brief Pause transition, call start() to continue
         *
         * @param currentTime
         */
        void pause(const TimeSize_t& currentTime);

        /**
         * @brief End transition to the target color
         *
         */
        void end();

        /**
         * @brief Reset transition to the start color
         *
         */
        void reset();

        /**
         * @brief Update transition
         *
         * @param currentTime
         */
        void update(const TimeSize_t& currentTime);

        /**
         * @brief Get current point
         *
         * @return Vector4D_t
         */
        inline Vector4D_t getValue()
        {
            return Vector4D_t(_data.x_transition.getValue(),
                              _data.y_transition.getValue(),
                              _data.w_transition.getValue(),
                              _data.h_transition.getValue());
        }

        /**
         * @brief Is transition finish
         *
         * @return true
         * @return false
         */
        inline bool isFinish()
        {
            return _data.x_transition.isFinish() && _data.y_transition.isFinish() && _data.w_transition.isFinish() &&
                   _data.h_transition.isFinish();
        }
    };

    /**
     * @brief A class to represent RGBA color with smooth transition.
     *
     */
    class SmoothRGBA : public Transition4D
    {
    public:
        SmoothRGBA() = default;
        SmoothRGBA(const int& red, const int& green, const int& blue, const int& alpha) { jumpTo(red, green, blue, alpha); }
        SmoothRGBA(const RGBA_t& colorStart) { jumpTo(colorStart.red, colorStart.green, colorStart.blue, colorStart.alpha); }

        /**
         * @brief Jump to target color without transition
         *
         * @param red
         * @param green
         * @param blue
         * @param alpha
         */
        inline void jumpTo(const int& red, const int& green, const int& blue, const int& alpha)
        {
            Transition4D::jumpTo(red, green, blue, alpha);
        }
        inline void jumpTo(const RGBA_t color) { jumpTo(color.red, color.green, color.blue, color.alpha); }

        /**
         * @brief Move to target point with transition
         *
         * @param red
         * @param green
         * @param blue
         * @param alpha
         */
        inline void moveTo(const int& red, const int& green, const int& blue, const int& alpha)
        {
            Transition4D::moveTo(red, green, blue, alpha);
        }
        inline void moveTo(const RGBA_t color) { moveTo(color.red, color.green, color.blue, color.alpha); }

        inline const int& getCurrentRed() { return getXTransition().getValue(); }
        inline const int& getCurrentGreen() { return getYTransition().getValue(); }
        inline const int& getCurrentBlue() { return getWTransition().getValue(); }
        inline const int& getCurrentAlpha() { return getHTransition().getValue(); }
        inline RGBA_t getCurrentColor() { return getValue(); }
    };
} // namespace SmoothUIToolKit
