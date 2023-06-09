/**
 * @file menu.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "menu.h"


namespace SMOOTH_MENU {


    int Menu_t::addItem(Item_t* item)
    {
        /* If null pointer */
        if (item == nullptr) {
            return -1;
        }

        /* Get ID */
        item->id = _item_list.size();

        /* Push into list */
        _item_list.push_back(item);

        return item->id;
    }


    int Menu_t::addItem(std::string tag, int x, int y, int width, int heigh, void* userData)
    {
        Item_t* new_item = new Item_t;

        new_item->tag = tag;
        new_item->x = x;
        new_item->y = y;
        new_item->width = width;
        new_item->heigh = heigh;
        new_item->userData = userData;
        
        return addItem(new_item);
    }


    int Menu_t::addItemVertically(std::string tag, int width, int heigh, int x, void* userData)
    {
        int y;
        if (_item_list.size() == 0) {
            y = 0;
        }
        else {
            y = _item_list[_item_list.size() - 1]->y + _item_list[_item_list.size() - 1]->heigh;
        }

        return addItem(tag, x, y, width, heigh, userData);
    }


    int Menu_t::addItemHorizontally(std::string tag, int width, int heigh, int y, void* userData)
    {
        int x;
        if (_item_list.size() == 0) {
            x = 0;
        }
        else {
            x = _item_list[_item_list.size() - 1]->x + _item_list[_item_list.size() - 1]->width;
        }

        return addItem(tag, x, y, width, heigh, userData);
    }


    void Menu_t::clearAllItem()
    {
        /* Free list */
        std::vector<Item_t*>().swap(_item_list);
    }


    void Menu_t::renderMenu()
    {
        if (_render_callback == nullptr) {
            return;
        }

        /* Iterate item list */
        for (int i = 0; i < _item_list.size(); i++) {
            _render_callback->renderMenu(_item_list[i]);
        }
    }



}
