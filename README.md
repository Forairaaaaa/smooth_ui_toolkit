# Smooth UI Toolkit

轻量级的 C++ UI 动画工具集

- Spring 动画、Easing 动画插值
- Lvgl C++ 封装
- signal、ringbuffer ...

## Animate

基础动画插值类，可配置起止、循环方式、次数、动画类型等，默认动画类型为 **spring**

动画抽象深度借鉴 [Motion](https://motion.dev/)，多谢 Motion 哥

```cpp
Animate animation;

animation.start = 200;
animation.end = 600;
animation.repeat = -1;
animation.repeatType = animate_repeat_type::reverse;

// 这里调用 spring option ，则动画类型为 spring
animation.springOptions().bounce = 0.4;
animation.springOptions().visualDuration = 0.6;

// 如想要 easing 动画，调用 easing option 即可
// animation.easingOptions().easingFunction = ease::ease_out_quad;
// animation.easingOptions().duration = 0.3;

animation.init();
animation.play();

while (1) {
    // 更新
    animation.update();
    // 取值
    draw_ball(animation.value(), 233);
}
```

## AnimateValue

Animate 的派生类，大幅简化使用操作

```cpp
AnimateValue x = 100;
AnimateValue y = 225;

while (1) {
    x = get_mouse_x();
    y = get_mouse_y();
  
  	// 取值时自动更新
    draw_ball(x, y);
});
```

## UI HAL

库内部所使用的时间相关函数均来自：

```cpp
namespace ui_hal {

/**
 * @brief Get the number of milliseconds since running
 *
 * @return uint32_t
 */
uint32_t get_tick();

/**
 * @brief Wait a specified number of milliseconds before returning
 *
 * @param ms
 */
void delay(uint32_t ms);

} // namespace ui_hal
```

其默认实现为 cpp chrono 库

如有需求，可自定义实现方式：

```cpp
// Arduino 为例

ui_hal::on_get_tick_ms([]() {
    return millis();
});

ui_hal::on_delay([](uint32_t ms) {
    delay(ms);
});
```

## Lvgl Cpp

再见吧👋 lv_obj_del，指针管理参考：*https://github.com/vpaeder/lvglpp*

```cpp
#include <smooth_lvgl.h>

// Basic lvgl object
auto obj = new Container(lv_screen_active());
obj->setPos(50, 50);
obj->setSize(200, 100);

// Label
auto label = new Label(lv_screen_active());
label->setTextFont(&lv_font_montserrat_24);
label->setAlign(LV_ALIGN_CENTER);
label->setText("????????????");

// Button
int count = 0;
auto btn = new Button(lv_screen_active());
btn->setPos(50, 200);
btn->label().setText("+1");
btn->onClick().connect([&]() { label->setText(fmt::format("{}", count++)); });

// Switch
auto sw = new Switch(lv_screen_active());
sw->setPos(50, 300);
sw->onValueChanged().connect([&](bool value) { label->setText(value ? "ON" : "OFF"); });

// Slider
auto slider = new Slider(lv_screen_active());
slider->setPos(50, 400);
slider->onValueChanged().connect([&](int value) { label->setText(fmt::format("{}", value)); });
```

## 编译例程

```bash
git clone https://github.com/Forairaaaaa/smooth_ui_toolkit.git
```

```bash
cd smooth_ui_toolkit && mkdir build
```

```bash
cd build && cmake .. && make -j8
```

cmake 过程会拉取 example 的依赖仓库，确保网络正常访问

