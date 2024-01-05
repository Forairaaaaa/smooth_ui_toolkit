/**
 * @file select_menu.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "../core/transition2d/transition2d.h"


namespace SmoothUIToolKit
{
    /**
     * @brief Abstraction of select menu 
     */
    class SelectMenu
    {
    public:
        struct Config_t
        {

        };

        struct Callback_t
        {

        };
        
    private:
        struct Data_t
        {
            
        };
        Data_t _data;
        Config_t _config;
        Callback_t _callback;

    public:
        // Configs  
        inline const Config_t& getConfig() { return _config; }
        inline void setConfig(Config_t cfg) { _config = cfg; }
        inline Config_t& setConfig() { return _config; }

        // Callbacks 
        inline const Callback_t& getCallback() { return _callback; }
        inline void setCallback(Callback_t callback) { _callback = callback; }
        inline Callback_t& setCallback() { return _callback; }

        /**
         * @brief Update menu 
         * 
         * @param currentTime 
         */
        void update(const std::uint32_t currentTime);

        /**
         * @brief Tell selector to go to last one item 
         * 
         */
        void goLast();

        /**
         * @brief Tell selector to go to the next item 
         * 
         */
        void goNext();
    };
}
