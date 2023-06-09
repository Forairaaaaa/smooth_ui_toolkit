/**
 * @file selector.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../lv_anim/lv_anim.h"
#include "../menu/menu.h"


namespace SMOOTH_MENU {


    struct SelectorRenderCallback_t {
        virtual void renderSelector(int x, int y, int width, int heigh) { }
    };


    namespace SELECTOR {

        struct Config_t {
            LVGL::LV_ANIM_PATH_t animPath_x = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_y = LVGL::ease_out;
            LVGL::LV_ANIM_PATH_t animPath_width = LVGL::overshoot;
            LVGL::LV_ANIM_PATH_t animPath_heigh = LVGL::ease_out;
            int32_t animTime = 400;
        };

        struct Shape_t {
            int x = 0;
            int y = 0;
            int width = 0;
            int heigh = 0;
        };

    };


    class Selector_t {
        private:
            SELECTOR::Config_t _cfg;
            SELECTOR::Shape_t _shape;

            Menu_t* _current_menu;

            unsigned int _current_item;
            unsigned int _target_item;
            bool _target_changed;

            LVGL::Anim_Path _anim_x;
            LVGL::Anim_Path _anim_y;
            LVGL::Anim_Path _anim_width;
            LVGL::Anim_Path _anim_heigh;

            SelectorRenderCallback_t* _render_callback;



        public:
            Selector_t()
            {
                _current_menu = nullptr;
                _current_item = 0;
                _target_item = 0;
                _target_changed = false;
                _render_callback = nullptr;

                _anim_x.setAnim(LVGL::overshoot, 0, 0, 0);
                _anim_y.setAnim(LVGL::ease_out, 0, 0, 0);
                _anim_width.setAnim(LVGL::overshoot, 0, 0, 0);
                _anim_heigh.setAnim(LVGL::ease_out, 0, 0, 0);
            }
            ~Selector_t() = default;


            inline unsigned int getCurrentItem() { return _current_item; }
            inline unsigned int getTargetItem() { return _target_item; }


            /**
             * @brief Set menu that selector base on
             * 
             * @param menu 
             */
            void setMenu(Menu_t* menu);


            /**
             * @brief Go to item, 0 ~ (getItemNum() - 1)
             * 
             * @param targetItem 
             */
            void goToItem(unsigned int targetItem);


            /**
             * @brief Go to last one
             * 
             */
            void goLast();


            /**
             * @brief Go to next one
             * 
             */
            void goNext();




            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(SelectorRenderCallback_t* callback) { _render_callback = callback; }


            void update(uint32_t currentTime);






    };


}
