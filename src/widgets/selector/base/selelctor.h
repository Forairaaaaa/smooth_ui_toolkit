/**
 * @file selelctor.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../../base/base.h"
#include "option.h"
#include <cstddef>
#include <functional>

namespace SmoothUIToolKit
{
    namespace Widgets
    {
        namespace Selector
        {
            /**
             * @brief Provide widget selector behavior abstraction
             *
             */
            class SelectorBase
            {
            private:
                struct SelectorBaseData_t
                {
                    WidgetBase* current_widget = nullptr;
                    bool move_in_loop = true;
                    int hovering_option_index = -1;
                };
                SelectorBaseData_t _selector_base_data;

            public:
                inline void moveInloop(bool moveInLoop) { _selector_base_data.move_in_loop = moveInLoop; }
                inline size_t getOptionNum() { return _selector_base_data.current_widget->getChildren().size(); }
                inline int getHoveringOptionIndex() { return _selector_base_data.hovering_option_index; }
                WidgetBase* getHoveringWidget();
                bool isHoveringOptionSelected();

            public:
                /**
                 * @brief Enter a widget
                 *
                 * @param widget
                 */
                virtual void enter(WidgetBase* widget);

                /**
                 * @brief Go back to last widget
                 *
                 * @return true
                 * @return false
                 */
                virtual bool back();

                virtual void goLast();

                virtual void goNext();

                virtual void goTo(int optionIndex);

                virtual void selectOption();

                virtual void unSelectOption();

            public:
                virtual void onEnter() {}
                virtual void onBack() {}
                virtual void onGoLast() {}
                virtual void onGoNext() {}
                virtual void onGoTo() {}
                virtual void onSelectOption() {}
                virtual void onUnSelectOption() {}
            };
        } // namespace Selector
    }     // namespace Widgets
} // namespace SmoothUIToolKit
