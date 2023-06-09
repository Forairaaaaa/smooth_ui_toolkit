/**
 * @file smooth_menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-06-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>


namespace SMOOTH_MENU {

    struct Item_t {
        /* Data */
        std::string tag;
        void* userData = nullptr;
        
        /* Postion */
        int x = 0;
        int y = 0;
        int width = 0;
        int heigh = 0;

        uint16_t id = 0;
    };


    class Menu : public Item_t {
        private:
            std::vector<Item_t*> _itemList;


        public:

            /**
             * @brief Add item into item list
             * 
             * @param item 
             * @return uint16_t Item ID
             */
            uint16_t addItem(Item_t* item);

            /**
             * @brief Add item into item list
             * 
             * @param tag 
             * @param x 
             * @param y 
             * @param width 
             * @param heigh 
             * @param userData 
             * @return uint16_t 
             */
            uint16_t addItem(std::string tag, int x, int y, int width, int heigh, void* userData = nullptr);


    };








}

