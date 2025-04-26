# Smooth UI Toolkit

C++ UI 动画工具集

- Spring 动画、Easing 动画插值
- Lvgl C++ 封装
- signal、ringbuffer ...

![](https://pic1.imgdb.cn/item/680c639c58cb8da5c8ce22d2.gif)

![](https://pic1.imgdb.cn/item/680c58b558cb8da5c8ce1f5b.gif)

![](https://pic1.imgdb.cn/item/680c58b458cb8da5c8ce1f5a.gif)

## Animate

基础动画插值类，可配置起止、循环方式、次数、动画类型等，默认动画类型为 **spring**

插值类抽象深受 [Motion](https://motion.dev/) 启发，多谢 Motion 哥

![](https://pic1.imgdb.cn/item/680c58b458cb8da5c8ce1f57.gif)

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

Animate 的派生类，大幅简化赋值、取值操作

适合控件坐标、长宽等参数的快速动画化：

视频：[介绍](https://www.bilibili.com/video/BV1RZcTegEUu)

![](https://pic1.imgdb.cn/item/680c58b458cb8da5c8ce1f58.gif)

```cpp
AnimateValue x = 100;
AnimateValue y = 225;

while (1) {
    // 赋值时自动适应新目标
    x = get_mouse_x();
    y = get_mouse_y();
  
    // 取值时自动更新、类型转换
    draw_ball(x, y);
});
```

## Lvgl Cpp

再见吧👋 lv_obj_del，可以用智能指针来管理 lvgl 控件了

指针管理参考：*https://github.com/vpaeder/lvglpp*

用了类似 Godot Signal 的信号槽来简化原来的 event 回调

![](https://pic1.imgdb.cn/item/680c58b458cb8da5c8ce1f59.gif)

```cpp
#include <smooth_lvgl.h>
// lvgl cpp 封装为 header only
// 需要工程已满足 #include <lvgl.h> 依赖
// 当前目标版本为 v9.2.2

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
btn->onClick().connect([&]() {
    label->setText(fmt::format("{}", count++));
});

// Switch
auto sw = new Switch(lv_screen_active());
sw->setPos(50, 300);
sw->onValueChanged().connect([&](bool value) {
    label->setText(value ? "ON" : "OFF");
});

// Slider
auto slider = new Slider(lv_screen_active());
slider->setPos(50, 400);
slider->onValueChanged().connect([&](int value) {
    label->setText(fmt::format("{}", value));
});
```

## UI HAL

动画的更新以系统时间为参考基准，所使用的相关函数来自内部定义：

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
// Arduino 为例，性能应该比 chrono 好

ui_hal::on_get_tick_ms([]() {
    return millis();
});

ui_hal::on_delay([](uint32_t ms) {
    delay(ms);
});
```

## 编译例程

例程里用到了 [lvgl](https://github.com/lvgl/lvgl) 和 [raylib](https://github.com/raysan5/raylib) 作为图形库，所以要安装 [SDL2](https://github.com/libsdl-org/SDL)

### 工具链安装:

- **macOS:**  `brew install sdl2 cmake make`  
- **Ubuntu:**   `sudo apt install build-essential cmake libsdl2-dev`  

### 拉取项目：

```bash
git clone https://github.com/Forairaaaaa/smooth_ui_toolkit.git
```

### 编译：

```bash
cd smooth_ui_toolkit && mkdir build
```

```bash
cd build && cmake .. && make -j8
```

cmake 过程过程中会拉取依赖 git 仓库，确保网络正常访问

## 库引入

### CMake工程

工程 `CMakeLists.txt` 里添加：

```cmake
# 不编译例程
set(SMOOTH_UI_TOOLKIT_BUILD_EXAMPLE OFF)

# 引入库路径
add_subdirectory(path/to/smooth_ui_toolkit)

# link
target_link_libraries(your_project PUBLIC
    smooth_ui_toolkit
)
```

### IDF 工程

clone 仓库，直接丢到 `components` 目录里就行

### PIO 工程

clone 仓库，直接丢到 `libs` 目录里就行

### Arduino 工程

clone 仓库，直接丢到 `xxx` 目录里就行（我不记得那个 library 目录叫什么了）

## TODO

- [ ] ui_hal 的内部 cpp 实现添加宏定义，避免在自定义实现时多余的 linkage
- [ ] NumberFlow 类在 linux 上有 bug，DigitFlow 正常
- [ ] AnimateVlaue 如果设置了 delay，只会在第一次有效，retarget 后无效
- [ ] 脚本化 lvgl widget api 封装

