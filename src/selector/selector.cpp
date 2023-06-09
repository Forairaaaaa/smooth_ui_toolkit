/**
 * @file selector.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "selector.h"


namespace SMOOTH_MENU {


    void Selector_t::setMenu(Menu_t* menu)
    {
        if (menu->getItemNum() == 0) {
            return;
        }

        _current_menu = menu;

        _shape.x = _current_menu->getItemList()[0]->x;
        _shape.y = _current_menu->getItemList()[0]->y;
        _shape.width = _current_menu->getItemList()[0]->width;
        _shape.heigh = _current_menu->getItemList()[0]->heigh;

        _current_item = 0;
        _target_item = 0;
        _target_changed = true;

    }


    void Selector_t::goToItem(unsigned int targetItem)
    {
        if (targetItem > (_current_menu->getItemNum() - 1)) {
            targetItem = _current_menu->getItemNum() - 1;
        }

        _target_item = targetItem;
        _target_changed = true;
    }


    void Selector_t::goLast()
    {
        if (_target_item == 0) {
            return;
        }
        goToItem(_target_item - 1);
    }


    void Selector_t::goNext()
    {
        goToItem(_target_item + 1);
    }


    void Selector_t::update(uint32_t currentTime)
    {
        /* If target changed */
        if (_target_changed) {
            _target_changed = false;

            /* Reset target */
            _anim_x.setAnim(_cfg.animPath_x, _anim_x.getValue(currentTime), _current_menu->getItemList()[_target_item]->x, _cfg.animTime);
            _anim_y.setAnim(_cfg.animPath_y, _anim_y.getValue(currentTime), _current_menu->getItemList()[_target_item]->y, _cfg.animTime);
            _anim_width.setAnim(_cfg.animPath_width, _anim_width.getValue(currentTime), _current_menu->getItemList()[_target_item]->width, _cfg.animTime);
            _anim_heigh.setAnim(_cfg.animPath_heigh, _anim_heigh.getValue(currentTime), _current_menu->getItemList()[_target_item]->heigh, _cfg.animTime);
            
            /* Reset anim time */
            _anim_x.resetTime(currentTime);
            _anim_y.resetTime(currentTime);
            _anim_width.resetTime(currentTime);
            _anim_heigh.resetTime(currentTime);

        }


        /* Render selector */
        if (_render_callback != nullptr) {
            _render_callback->renderSelector(_anim_x.getValue(currentTime), _anim_y.getValue(currentTime), _anim_width.getValue(currentTime), _anim_heigh.getValue(currentTime));
        }

        /* Render menu */
        _current_menu->renderMenu();

    }

}


