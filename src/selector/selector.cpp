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


    Selector_t::Selector_t()
    {
        _current_menu = nullptr;
        _render_callback = nullptr;

        /* Set to default */
        {
            SELECTOR::Config_t default_config;
            SELECTOR::AnimContainer_t default_anim_cntr;
            SELECTOR::ItemStatus_t default_item_status;
            _cfg = default_config;
            _anim_cntr = default_anim_cntr;
            _item_status = default_item_status;
        }
    }


    void Selector_t::setMenu(Menu_t* menu)
    {
        _current_menu = menu;
        _item_status.current = 0;
        _item_status.target = 0;
        _item_status.changed = true;
    }


    void Selector_t::goToItem(unsigned int targetItem)
    {
        if (targetItem > (_current_menu->getItemNum() - 1)) {
            targetItem = _current_menu->getItemNum() - 1;
        }

        _item_status.target = targetItem;
        _item_status.changed = true;
    }


    void Selector_t::goLast()
    {
        if (_item_status.target == 0) {
            return;
        }
        goToItem(_item_status.target - 1);
    }


    void Selector_t::goNext()
    {
        goToItem(_item_status.target + 1);
    }


    void Selector_t::update(uint32_t currentTime, bool renderAtOnce)
    {
        /* If target changed */
        if (_item_status.changed) {
            _item_status.changed = false;

            /* Reset anim to target */
            _anim_cntr.x.setAnim(_cfg.animPath_x, _anim_cntr.x.getValue(currentTime), _current_menu->getItemList()[_item_status.target]->x, _cfg.animTime_x);
            _anim_cntr.y.setAnim(_cfg.animPath_y, _anim_cntr.y.getValue(currentTime), _current_menu->getItemList()[_item_status.target]->y, _cfg.animTime_y);
            _anim_cntr.width.setAnim(_cfg.animPath_width, _anim_cntr.width.getValue(currentTime), _current_menu->getItemList()[_item_status.target]->width, _cfg.animTime_width);
            _anim_cntr.height.setAnim(_cfg.animPath_height, _anim_cntr.height.getValue(currentTime), _current_menu->getItemList()[_item_status.target]->height, _cfg.animTime_height);
            
            /* Reset anim time */
            _anim_cntr.x.resetTime(currentTime);
            _anim_cntr.y.resetTime(currentTime);
            _anim_cntr.width.resetTime(currentTime);
            _anim_cntr.height.resetTime(currentTime);

            
        }

        /* Update current time */
        _anim_cntr.currentTime = currentTime;

        /* Render menu and selector */
        if (renderAtOnce) {
            render();
        }
    }


    void Selector_t::render(bool renderMenu)
    {
        /* Render selector */
        if (_render_callback != nullptr) {
            _render_callback->renderCallback(
                _anim_cntr.x.getValue(_anim_cntr.currentTime),
                _anim_cntr.y.getValue(_anim_cntr.currentTime),
                _anim_cntr.width.getValue(_anim_cntr.currentTime),
                _anim_cntr.height.getValue(_anim_cntr.currentTime)
            );
        }

        /* Render menu */
        if (renderMenu) {
            _current_menu->render();
        }
    }


    bool Selector_t::isAnimFinished()
    {
        if (!_anim_cntr.x.isFinished(_anim_cntr.currentTime)) {
            return false;
        }
        if (!_anim_cntr.y.isFinished(_anim_cntr.currentTime)) {
            return false;
        }
        if (!_anim_cntr.width.isFinished(_anim_cntr.currentTime)) {
            return false;
        }
        if (!_anim_cntr.height.isFinished(_anim_cntr.currentTime)) {
            return false;
        }
        _item_status.current = _item_status.target;
        return true;
    }


    const RenderAttribute_t& Selector_t::getRenderAttribute()
    {
        _render_attribute_buffer.x = _anim_cntr.x.getValue(_anim_cntr.currentTime);
        _render_attribute_buffer.y = _anim_cntr.y.getValue(_anim_cntr.currentTime);
        _render_attribute_buffer.width = _anim_cntr.width.getValue(_anim_cntr.currentTime);
        _render_attribute_buffer.height = _anim_cntr.height.getValue(_anim_cntr.currentTime);

        return _render_attribute_buffer;
    }


}


