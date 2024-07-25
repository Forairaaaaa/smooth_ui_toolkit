/**
 * @file transition3d.h
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
#include "core/math/math.h"
#include <cstdint>
#include <functional>

namespace SmoothUIToolKit
{
    /**
     * @brief A container of 3 Transitions, provides dynamic transition methods
     *
     */
    class Transition3D
    {
    public:
        struct Config_t
        {
            std::function<void(Transition3D*)> updateCallback = nullptr;
        };

    private:
        struct Data_t
        {
            Transition x_transition;
            Transition y_transition;
            Transition z_transition;
            bool is_changed = true;
        };
        Data_t _data;
        Config_t _config;

    public:
        Transition3D() = default;
        Transition3D(const int& xStart, const int& yStart, const int& zStart) { jumpTo(xStart, yStart, zStart); }
        Transition3D(const Vector3D_t& pSatrt) { jumpTo(pSatrt); }

        // Basic setter
        inline void setDuration(TimeSize_t duration)
        {
            _data.x_transition.setDuration(duration);
            _data.y_transition.setDuration(duration);
            _data.z_transition.setDuration(duration);
        }
        inline void setDelay(TimeSize_t delay)
        {
            _data.x_transition.setDelay(delay);
            _data.y_transition.setDelay(delay);
            _data.z_transition.setDelay(delay);
        }
        inline void setTransitionPath(EasingPath_t transitionPath)
        {
            _data.x_transition.setTransitionPath(transitionPath);
            _data.y_transition.setTransitionPath(transitionPath);
            _data.z_transition.setTransitionPath(transitionPath);
        }
        inline void setUpdateCallback(std::function<void(Transition3D*)> callback) { _config.updateCallback = callback; }

        // Basic getter
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }
        inline Transition& getZTransition() { return _data.z_transition; }
        inline Vector3D_t getStartPoint()
        {
            return Vector3D_t(
                _data.x_transition.getStartValue(), _data.y_transition.getStartValue(), _data.z_transition.getStartValue());
        }
        inline Vector3D_t getTargetPoint()
        {
            return Vector3D_t(
                _data.x_transition.getEndValue(), _data.y_transition.getEndValue(), _data.z_transition.getEndValue());
        }

        // Helper setter
        inline void setEachDuration(TimeSize_t x, TimeSize_t y, TimeSize_t z)
        {
            _data.x_transition.setDuration(x);
            _data.y_transition.setDuration(y);
            _data.z_transition.setDuration(z);
        }
        inline void setEachDelay(TimeSize_t x, TimeSize_t y, TimeSize_t z)
        {
            _data.x_transition.setDelay(x);
            _data.y_transition.setDelay(y);
            _data.z_transition.setDelay(z);
        }
        inline void setEachTransitionPath(EasingPath_t x, EasingPath_t y, EasingPath_t z)
        {
            _data.x_transition.setTransitionPath(x);
            _data.y_transition.setTransitionPath(y);
            _data.z_transition.setTransitionPath(z);
        }

    public:
        /**
         * @brief Jump to target point without transition
         *
         * @param x
         * @param y
         * @param z
         */
        void jumpTo(const int& x, const int& y, const int& z);
        inline void jumpTo(const Vector3D_t& p) { jumpTo(p.x, p.y, p.z); }

        /**
         * @brief Move to target point with transition
         *
         * @param x
         * @param y
         * @param z
         */
        void moveTo(const int& x, const int& y, const int& z);
        inline void moveTo(const Vector3D_t& p) { moveTo(p.x, p.y, p.z); }

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
         * @return Vector3D_t
         */
        inline Vector3D_t getValue()
        {
            return Vector3D_t(_data.x_transition.getValue(), _data.y_transition.getValue(), _data.z_transition.getValue());
        }

        /**
         * @brief Is transition finish
         *
         * @return true
         * @return false
         */
        inline bool isFinish()
        {
            return _data.x_transition.isFinish() && _data.y_transition.isFinish() && _data.z_transition.isFinish();
        }
    };

    /**
     * @brief A class to represent RGB color with smooth transition.
     *
     */
    class SmoothRGB : public Transition3D
    {
    public:
        SmoothRGB() = default;
        SmoothRGB(const int& red, const int& green, const int& blue) { jumpTo(red, green, blue); }
        SmoothRGB(const RGB_t& colorStart) { jumpTo(colorStart); }
        SmoothRGB(const std::uint32_t& colorSatrt) { jumpTo(colorSatrt); }

        /**
         * @brief Jump to target color without transition
         *
         * @param red
         * @param green
         * @param blue
         */
        inline void jumpTo(const int& red, const int& green, const int& blue) { Transition3D::jumpTo(red, green, blue); }
        inline void jumpTo(const RGB_t color) { jumpTo(color.red, color.green, color.blue); }
        inline void jumpTo(const std::uint32_t& color) { jumpTo(Hex2Rgb(color)); }

        /**
         * @brief Move to target point with transition
         *
         * @param red
         * @param green
         * @param blue
         */
        inline void moveTo(const int& red, const int& green, const int& blue) { Transition3D::moveTo(red, green, blue); }
        inline void moveTo(const RGB_t color) { moveTo(color.red, color.green, color.blue); }
        inline void moveTo(const std::uint32_t& color) { moveTo(Hex2Rgb(color)); }

        inline const int& getCurrentRed() { return getXTransition().getValue(); }
        inline const int& getCurrentGreen() { return getYTransition().getValue(); }
        inline const int& getCurrentBlue() { return getZTransition().getValue(); }
        inline RGB_t getCurrentColor() { return getValue(); }
        inline uint32_t getCurrentColorHex() { return Rgb2Hex(getValue()); }
    };
} // namespace SmoothUIToolKit
