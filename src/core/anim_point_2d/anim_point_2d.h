/**
 * @file anim_point_2d.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../types/types.h"
#include "lv_anim/lv_anim.h"


namespace SMOOTH_UI_TK
{
    class AnimPoint2D
    {
    public:
        struct Config_t 
        {
            LVGL::LV_ANIM_PATH_t anim_path_x = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t anim_path_y = LVGL::ease_out;
            int32_t anim_time_x = 400;
            int32_t anim_time_y = 400;
        };

    private:
        struct Data_t
        {
            // TODO: deprecate "Anim_Path", abstract an anim 1D instead
            // to remove multiple target buffer, and better path config 
            LVGL::Anim_Path anim_x;
            LVGL::Anim_Path anim_y;
            Point2D_Int_t current_point;
            Point2D_Int_t target_point;
            bool is_target_changed = false;
        };
        Data_t _data;
        Config_t _config;

        void _move_to_no_anim(int x, int y);

    public:
        AnimPoint2D(int xStart = 0, int yStart = 0);
        inline AnimPoint2D(Point2D_Int_t point2d) { AnimPoint2D(point2d.x, point2d.y); }

        inline Config_t getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        
        /**
         * @brief Move to the target point 
         * 
         * @param x 
         * @param y 
         */
        void moveTo(int x, int y);
        inline void moveTo(Point2D_Int_t point2d) { moveTo(point2d.x, point2d.y); }

        /**
         * @brief Move to the target point without anim 
         * 
         * @param x 
         * @param y 
         */
        inline void moveToWithNoAnim(int x, int y) { _move_to_no_anim(x, y); }

        /**
         * @brief Update point 
         * 
         * @param currentTime 
         */
        void update(uint32_t currentTime);

        inline const Point2D_Int_t& getCurentPoint() { return _data.current_point; }
        inline int x() { return _data.current_point.x; }
        inline int y() { return _data.current_point.y; }
    };
}
