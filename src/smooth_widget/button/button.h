/**
 * @file button.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "../base/base.h"


namespace SmoothUIToolKit 
{ 
    namespace SmoothWidget 
    {
        class Button;

        typedef void (*ButtonOnUpdateCallback)(Button*);
        typedef void (*ButtonOnhoverCallback)(Button*);
        typedef void (*ButtonOnPressCallback)(Button*);
        typedef void (*ButtonOnPressStartCallback)(Button*);
        typedef void (*ButtonOnPressEndCallback)(Button*);

        class Button :public WidgetBase
        {
        public:
            struct Callback_t
            {
                ButtonOnUpdateCallback onUpdate = nullptr;
                ButtonOnhoverCallback onHover = nullptr;
                ButtonOnPressCallback onPress = nullptr;
                ButtonOnPressStartCallback onPressStart = nullptr;
                ButtonOnPressEndCallback onPressEnd = nullptr;
            };

            struct Config_t
            {
                Callback_t callback;
            };

        private:
            Config_t _config;

        public:
            Button() = default;
            Button(int x, int y, int width, int height) : WidgetBase(x, y, width, height) {}
            Button(Vector2D_t position, Vector2D_t size) : WidgetBase(position, size) {}

            // Config 
            inline const Config_t& getConfig() { return _config; }
            inline Config_t& setConfig() { return _config; }
            inline Callback_t& setCallback() { return _config.callback; }

        protected:
            // Core methods 
            void update(std::uint32_t currentTime) override;
            void hover(int x, int y) override;
            void drag(int x, int y) override;
            void drop() override;

        protected:
            // Internal core methods callback for derived button 
            virtual void _onUpdate() {}
            virtual void _onHover() {}
            virtual void _onDrag() {}
            virtual void _onDrop() {}
        };
    }
}
