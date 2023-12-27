/**
 * @file dragger.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../lv_anim/lv_anim.h"

namespace SMOOTH_UI_TK
{
    struct Config_t
    {
        LVGL::LV_ANIM_PATH_t animPath_x = LVGL::ease_out;
        LVGL::LV_ANIM_PATH_t animPath_y = LVGL::ease_out;
        int32_t animTime_x = 100;
        int32_t animTime_y = 100;
    };

    struct AnimContainer_t
    {
        LVGL::Anim_Path x;
        LVGL::Anim_Path y;
        uint32_t currentTime = 0;
    };

    struct Data_t
    {

    };

    class Dragger_t
    {
    protected:
        Config_t _config;
        AnimContainer_t _anim_cntr;
        Data_t _data;

        void _reset_anim_time();

    public:
        Dragger_t();
        

    };
}
