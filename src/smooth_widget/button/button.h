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
            struct Callbacks_t
            {
                ButtonOnUpdateCallback onUpdate = nullptr;
                ButtonOnhoverCallback onHover = nullptr;
                ButtonOnPressCallback onPress = nullptr;
                ButtonOnPressStartCallback onPressStart = nullptr;
                ButtonOnPressEndCallback onPressEnd = nullptr;
            };

        private:
            Callbacks_t _callbacks;
            // TODO (helpers)

        public:
            Button() = default;
            Button(int x, int y, int width, int height) : WidgetBase(x, y, width, height) {}
            Button(Vector2D_t position, Vector2D_t size) : WidgetBase(position, size) {}

            // TODO (overrides)

        };
    }
}
