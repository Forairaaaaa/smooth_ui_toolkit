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
#include <cstdint>
#include <string>
#include <vector>

namespace SmoothUIToolKit {
/**
 * @brief Abstraction of select menu
 */
class SelectMenu {
  public:
    /**
     * @brief Properties of an option
     *
     */
    struct OptionProps_t {
        Vector2D_t position;
        Vector2D_t size;
        std::string tag;
        void* userData = nullptr;
    };

    /**
     * @brief Properties of selector
     *
     */
    struct SelectorProps_t {
        Transition2D position;
        Transition2D size;
    };

    /**
     * @brief Properties of camera
     *
     */
    struct CameraProps_t {
        Transition2D offset;
    };

    struct Callback_t {
        virtual void onRender(const std::vector<OptionProps_t>& optionProps,
                              const SelectorProps_t& selector,
                              const CameraProps_t& camera) {}
    };

    struct Config_t {};

  private:
    struct Data_t {
        // Options
        std::vector<OptionProps_t> option_list;
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
} // namespace SmoothUIToolKit
