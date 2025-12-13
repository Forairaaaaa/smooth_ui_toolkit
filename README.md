# Smooth UI Toolkit

- Spring、Easing 动画插值，RGB 颜色过渡插值
- Lvgl C++ 封装，NumberFlow 风格控件
- 动画菜单抽象
- 颜色类型定义，颜色混合、转换方法
- Signal、RingBuffer 等常用模板类
- Vector 类型，clamp、map_range 等数学工具

![Jul-26-2025 01-00-39](https://github.com/user-attachments/assets/1930f5e6-4a72-47e3-aa1e-e54335e3b4c2)

![Jul-26-2025 00-47-13](https://github.com/user-attachments/assets/2a3e9302-87df-438f-9c97-2c1dc7415cec)

![Jul-26-2025 01-07-33](https://github.com/user-attachments/assets/b47c41b4-8c73-4cc0-bb84-3efda0bda1ee)

## 动画组件

### Animate

基础动画插值类，默认动画类型为 **spring**

插值类抽象参考 [Motion](https://motion.dev/) ，多谢 Motion 哥

![](https://pic1.imgdb.cn/item/680c58b458cb8da5c8ce1f57.gif)

```cpp
Animate animation;

// 动画参数配置
animation.start = 200;
animation.end = 600;
animation.repeat = -1;
animation.repeatType = AnimateRepeatType::Reverse;

// spring 动画参数配置
// 这里调用 springOptions() ，动画类型自动适应为 spring
animation.springOptions().bounce = 0.4;
animation.springOptions().visualDuration = 0.6;

// 如想要 easing 动画，调用 easingOptions() 即可
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

### AnimateValue

Animate 的派生类，简化取值赋值操作，使用起来更接近于普通变量

适合控件的坐标、长宽等参数的过渡插值，来实现动画效果：[视频](https://www.bilibili.com/video/BV1RZcTegEUu)

![Jul-26-2025 01-24-37](https://github.com/user-attachments/assets/9ef569b6-5226-4365-bb20-2c16208866e4)

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

配合 [spring 参数](https://motion.dev/docs/spring#options) 可以实现不同的动画效果：

![Jul-26-2025 00-54-17](https://github.com/user-attachments/assets/1a63077a-6536-4081-a97a-fa9bf7c82faf)

```cpp
for (int i = 0; i < cursors.size(); i++) {
    // 弹簧刚度逐渐增加
    cursors[i].x.springOptions().stiffness = 55 + i * 25;
  	// 阻尼系数逐渐减小
    cursors[i].x.springOptions().damping = 13 - i;
}
```

## Lvgl Cpp 封装

Lvgl 控件智能指针封装

指针管理参考：*https://github.com/vpaeder/lvglpp*

添加了类似 Godot Signal 的观察者来简化事件处理

![Jul-26-2025 00-56-19](https://github.com/user-attachments/assets/4aa17149-6a3c-4b78-87cc-38150f12dcf2)

```cpp
#include <smooth_lvgl.hpp>
// lvgl cpp 封装为 header only
// 需要工程已满足 #include <lvgl.h> 依赖
// 当前目标版本为 v9.3.0

// Basic lvgl object
auto obj = new Container(screen);
obj->setPos(50, 50);
obj->setSize(200, 100);

// Label
auto label = new Label(screen);
label->setTextFont(&lv_font_montserrat_24);
label->align(LV_ALIGN_CENTER, -180, 0);
label->setText("??");

// Button
int count = 0;
auto btn = new Button(screen);
btn->setPos(50, 200);
btn->label().setText("+1");
btn->onClick().connect([&]() {
    label->setText(fmt::format("{}", count++));
});

// Switch
auto sw = new Switch(screen);
sw->setPos(50, 300);
sw->onValueChanged().connect([&](bool value) {
    label->setText(value ? "ON" : "OFF");
});

// Slider
auto slider = new Slider(screen);
slider->setPos(50, 390);
slider->onValueChanged().connect([&](int value) {
    label->setText(fmt::format("{}", value));
});

// Roller
auto roller = new Roller(screen);
roller->align(LV_ALIGN_CENTER, 0, 0);
roller->setOptions({"nihao", "wohao", "dajiahao"});
roller->onValueChanged().connect([&](uint32_t value) {
    label->setText(fmt::format("{}", roller->getSelectedStr()));
});

// ...
```

### NumberFlow

基于 Lvgl 实现的 [NumberFlow](https://number-flow.barvian.me/) 风格数字显示控件，支持正负、小数和前后缀显示

![Jul-26-2025 00-50-36](https://github.com/user-attachments/assets/4535f621-9ba8-4937-bbf2-2ce358d42929)

```cpp
auto number_flow = new NumberFlow(lv_screen_active());

...
btn_random->onClick().connect([&]() {
    number_flow->setValue(randomNum);
});

while (1) {
    number_flow->update();
}

```

#### 前后缀文本、颜色设置：

![Jul-26-2025 21-41-14](https://github.com/user-attachments/assets/edecc1ab-6f64-4b59-b3ba-2eb406cc390a)

```cpp
...
// 设置前缀颜色
number_flow->setPrefixColor(lv_color_hex(0x00b894));

// 设置数字颜色
number_flow->setDigitColor(lv_color_hex(0xa29bfe));

// 设置后缀颜色
number_flow->setSuffixColor(lv_color_hex(0xff4757));

number_flow->onClick().connect([&]() {

    // 设置前缀
    number_flow->setPrefix(get_random_prefix());

    // 设置后缀
    number_flow->setSuffix(get_random_suffix());

    ...
});
...
```

#### 小数支持：

![Jul-26-2025 21-52-02](https://github.com/user-attachments/assets/9e80e62b-612c-428a-bc9a-1ddeb807c1db)

```cpp
// 替换对象类型即可
auto number_flow = new NumberFlowFloat(lv_screen_active());
...
```

## 控件抽象

### SmoothSelectorMenu

基于选择器的菜单抽象，选择器会平滑移动和变形，来匹配选中选项的关键帧

摄像机会自动平滑移动，保持选择器在摄像机范围内

适合常见的横向或纵向列表菜单：

![Mix1](https://github.com/user-attachments/assets/01df49db-162e-428d-bce8-7bbc4f74702c)

![SmoothMenuDemo1](https://github.com/user-attachments/assets/d7b30adb-936f-4e1c-9376-cad8c06913cd)

简单横向菜单[例程](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/example/widget/horizontal_stack_menu.cpp) ：

![hstack-menu](https://github.com/user-attachments/assets/562f5da1-9a0d-4794-9a66-a590985f8782)

也可以通过坐标变换实现选择器固定不动，而是选项滚动

选择器固定的横向菜单[例程](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/example/widget/fixed_selector_h_stack_menu.cpp) ：

![fixed-selector-hstack-menu](https://github.com/user-attachments/assets/75a45977-9610-434a-8daf-f8a5e1eb262f)

选择器固定的纵向带弧度菜单[例程](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/example/widget/fixed_selector_v_stack_curved_menu.cpp) ：

![vstack-curved-menu](https://github.com/user-attachments/assets/b6699639-6968-4a5d-a6f6-aa03694f56e3)

可以看这个[例程](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/example/widget/smooth_selector_menu.cpp)来了解具体的实现功能：

![timerrelay](https://github.com/user-attachments/assets/988f5c44-8cc3-435a-a47a-603d92a20251)

### SmoothOptionsMenu

基于选项移动的菜单抽象，每个选项独立动画，循环轮换到关键帧位置

适合圆形旋转菜单、卡片轮播等菜单

![SmoothMenuDemo2](https://github.com/user-attachments/assets/d151aac9-8995-4939-8110-3e4037e8f8da)

可以看这个[例程](https://github.com/Forairaaaaa/smooth_ui_toolkit/blob/main/example/widget/smooth_options_menu.cpp)来了解具体的实现功能：

![asdasda](https://github.com/user-attachments/assets/de8f281e-6e58-4c41-b7fa-33fb628b32e7)

## 颜色

### 颜色转换、混合函数

```cpp
// 0xffffff -> rgb(255, 255, 255)
Rgb_t hex_to_rgb(const uint32_t& hex);

// "#ffffff" -> rgb(255, 255, 255)
Rgb_t hex_to_rgb(const std::string& hex);

// rgb(255, 255, 255) -> 0xffffff
uint32_t rgb_to_hex(const Rgb_t& rgb);

// rgb(255, 255, 255) -> "#ffffff"
std::string rgb_to_hex_string(const Rgb_t& rgb);

// 差值混合
Rgb_t blend_in_difference(Rgb_t bg, Rgb_t fg);

// 透明度混合
Rgb_t blend_in_opacity(Rgb_t bg, Rgb_t fg, float opacity);
```

### AnimateRgb_t

RGB 颜色的变换过渡插值

![Jul-26-2025 01-03-01](https://github.com/user-attachments/assets/0c4e521e-4fff-4423-926f-7eb9d288b4b8)

```cpp
// 颜色列表
std::vector<uint32_t> color_list = {...}

AnimateRgb_t bg_color;
bg_color.duration = 0.3;
bg_color.begin();

// 按钮事件
btn_random.onClick().connect([&]() {
  	// 直接赋值即可
    bg_color = color_list[random];
});

while (1) {
  	// 更新
    bg_color.update();
  	// 取值
    xxx.setBgColor(lv_color_hex(bg_color.toHex()));
}
```

## UI HAL

动画的更新以系统 Tick 为参考基准，所使用的相关函数来自内部定义：

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

默认实现为 chrono 和 thread

cmake 里 OFF `SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL` 

或者添加全局宏 `SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL=0`

可以关闭这个默认实现

自定义实现方式：

```cpp
// 比如 Arduino，性能应该比 chrono 好

ui_hal::on_get_tick([]() {
    return millis();
});

ui_hal::on_delay([](uint32_t ms) {
    delay(ms);
});
```

## 命名空间

所有类和方法均定义在命名空间 `smooth_ui_toolkit` 下

```cpp
smooth_ui_toolkit::clamp(...);
smooth_ui_toolkit::AnimateValue();
smooth_ui_toolkit::lvgl_cpp::Button(...);
...
```

可以引用 `<uitk/short_namespace.hpp>` 来获得一个更简短的重命名 `uitk`

```cpp
#include <smooth_ui_toolkit.hpp>
#include <uitk/short_namespace.hpp>

uitk::clamp(...);
uitk::AnimateValue();
uitk::lvgl_cpp::Button(...);
...
```

## 编译例程

例程用了 [lvgl](https://github.com/lvgl/lvgl) 和 [raylib](https://github.com/raysan5/raylib) 作为图形库，所以要安装 [SDL2](https://github.com/libsdl-org/SDL)

### 工具链安装：

- **macOS:**  `brew install sdl2 cmake make`  
- **Ubuntu:**   `sudo apt install build-essential cmake libsdl2-dev`  

### 拉取项目：

```bash
git clone https://github.com/Forairaaaaa/smooth_ui_toolkit.git
```

```bash
cd smooth_ui_toolkit
```

### 拉取依赖：

```bash
python example/fetch_repos.py
```

### 编译：

```bash
mkdir build && cd build
```

```bash
cmake .. && make -j8
```

### 运行：

执行 `./build/example/` 下对应例程，如：

```shell
./build/example/basic_animations
```

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

clone 仓库，直接丢到 `libraries` 目录里就行
