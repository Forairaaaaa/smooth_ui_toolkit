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


namespace SmoothUIToolKit
{
    class SmoothPoint
    {
    private:
        struct Data_t
        {
            Transition x_transition;
            Transition y_transition;
            Vector2D_t current_point;
        };
        Data_t _data;

    public:
        // Basic getter 
        inline Transition& getXTransition() { return _data.x_transition; }
        inline Transition& getYTransition() { return _data.y_transition; }

        /**
         * @brief Start moving  
         * 
         * @param currentTime 
         */
        void start(std::uint32_t currentTime);

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
        void update(std::uint32_t currentTime);

        /**
         * @brief Jump to target point with no transition 
         * 
         * @param p 
         */
        void jumpTo(const Vector2D_t& p);

        /**
         * @brief Move to target point smoothly 
         * 
         * @param p 
         */
        void moveTo(const Vector2D_t& p);

        /**
         * @brief Get current point  
         * 
         * @return int 
         */
        inline const Vector2D_t& getValue() { return _data.current_point; }

        /**
         * @brief Is moving finish 
         * 
         * @return true 
         * @return false 
         */
        inline bool isFinish() { return _data.x_transition.isFinish() && _data.y_transition.isFinish(); }
    };
}
