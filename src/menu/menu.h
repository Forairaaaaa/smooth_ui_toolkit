/**
 * @file menu.h
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

        int id = 0;
    };


    struct MenuRenderCallback_t {
        virtual void renderMenu(const Item_t* item) { }
    };


    class Menu_t : protected Item_t {
        private:
            std::vector<Item_t*> _item_list;
            MenuRenderCallback_t* _render_callback;

        public:
            Menu_t() : _render_callback(nullptr) {}
            ~Menu_t() = default;


            /**
             * @brief Get the Item List
             * 
             * @return std::vector<Item_t*> 
             */
            inline std::vector<Item_t*> getItemList() { return _item_list; }


            /**
             * @brief Add item into item list
             * 
             * @param tag 
             * @param x 
             * @param y 
             * @param width 
             * @param heigh 
             * @param userData 
             * @return int 
             */
            int addItem(std::string tag, int x, int y, int width, int heigh, void* userData = nullptr);


            /**
             * @brief Add item into item list
             * 
             * @param item 
             * @return int Item ID
             */
            int addItem(Item_t* item);


            /**
             * @brief Add item into menu vertically, automatically append Y
             * 
             * @param tag 
             * @param width 
             * @param heigh 
             * @param userData 
             * @return int 
             */
            int addItemVertically(std::string tag, int width, int heigh, int x = 0, void* userData = nullptr);


            /**
             * @brief Add item into menu horizontally, automatically append X
             * 
             * @param tag 
             * @param y 
             * @param width 
             * @param heigh 
             * @param userData 
             * @return ine 
             */
            int addItemHorizontally(std::string tag, int width, int heigh, int y = 0, void* userData = nullptr);


            /**
             * @brief Get the number of item in the menu
             * 
             * @return size_t 
             */
            inline size_t getItemNum() { return _item_list.size(); }


            /**
             * @brief Remove all items in menu
             * 
             */
            void clearAllItem();


            /**
             * @brief Set the Render Callback function, for your graphics lib
             * 
             * @param callback 
             */
            inline void setRenderCallback(MenuRenderCallback_t* callback) { _render_callback = callback; }


            /**
             * @brief Render menu at once
             * 
             */
            void renderMenu();


    };








}

