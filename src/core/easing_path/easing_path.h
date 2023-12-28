/**
 * @file easing_path.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../types/types.h"
#include "../cubic_bezier/cubic_bezier.h"
// Refs: 
// https://en.wikipedia.org/wiki/B%C3%A9zier_curve
// https://cubic-bezier.com
// https://easings.net
// https://github.com/lvgl/lvgl/blob/master/src/misc/lv_anim.h


namespace SMOOTH_UI_TK
{
    namespace EasingPath
    {
        /**
         * @brief Base class 
         * 
         */
        class EasingPath_t
        {
        private:
            Vector4D_t _control_points;

        public:
            /**
            * @brief Float for easy copy 
            * 
            * @param p0 
            * @param p1 
            * @param p2 
            * @param p3 
            */
            EasingPath_t(float p0, float p1, float p2, float p3);

            /**
            * @brief Get the Control Points
            * 
            * @return const Vector4D_t& 
            */
            inline const Vector4D_t& getControlPoints() { return _control_points; }

            /**
            * @brief Get B(t), t: 0~1024
            * 
            * @param t 
            * @return int 
            */
            virtual int getValue(int t) { return CubicBezierInt(t, _control_points); }
        };


        // Paths 
        // TODO: change to declare 
        static EasingPath_t easeInSine(0.12, 0, 0.39, 0);
        static EasingPath_t easeOutSine(0.61, 1, 0.88, 1);
        static EasingPath_t easeInOutSine(0.37, 0, 0.63, 1);
        static EasingPath_t easeInQuad(0.11, 0, 0.5, 0);
        static EasingPath_t easeOutQuad(0.5, 1, 0.89, 1);
        static EasingPath_t easeInOutQuad(0.45, 0, 0.55, 1);
        static EasingPath_t easeInCubic(0.32, 0, 0.67, 0);
        static EasingPath_t easeOutCubic(0.33, 1, 0.68, 1);
        static EasingPath_t easeInOutCubic(0.65, 0, 0.35, 1);
        static EasingPath_t easeInQuart(0.5, 0, 0.75, 0);
        static EasingPath_t easeOutQuart(0.25, 1, 0.5, 1);
        static EasingPath_t easeInOutQuart(0.76, 0, 0.24, 1);
        static EasingPath_t easeInQuint(0.64, 0, 0.78, 0);
        static EasingPath_t easeOutQuint(0.22, 1, 0.36, 1);
        static EasingPath_t easeInOutQuint(0.83, 0, 0.17, 1);
        static EasingPath_t easeInExpo(0.7, 0, 0.84, 0);
        static EasingPath_t easeOutExpo(0.16, 1, 0.3, 1);
        static EasingPath_t easeInOutExpo(0.87, 0, 0.13, 1);
        static EasingPath_t easeInCirc(0.55, 0, 1, 0.45);
        static EasingPath_t easeOutCirc(0, 0.55, 0.45, 1);
        static EasingPath_t easeInOutCirc(0.85, 0, 0.15, 1);
        static EasingPath_t easeInBack(0.36, 0, 0.66, -0.56);
        static EasingPath_t easeOutBack(0.34, 1.56, 0.64, 1);
        static EasingPath_t easeInOutBack(0.68, -0.6, 0.32, 1.6);


        // Special paths
        // TODO
    }
}
