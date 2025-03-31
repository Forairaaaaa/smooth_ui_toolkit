include(FetchContent)

# Dependencies
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

set(MOONCAKE_LOG_BUILD_EXAMPLE OFF)
FetchContent_Declare(
    mooncake_log
    GIT_REPOSITORY https://github.com/Forairaaaaa/mooncake_log.git
    GIT_TAG main
)
FetchContent_MakeAvailable(mooncake_log)

set(LV_CONF_INCLUDE_SIMPLE OFF)
set(LV_CONF_PATH ${CMAKE_SOURCE_DIR}/example/utils/lv_conf.h)
FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl.git
    GIT_TAG v9.2.2
)
FetchContent_MakeAvailable(lvgl)

find_package(SDL2 REQUIRED SDL2)
include_directories(PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(lvgl PUBLIC ${SDL2_INCLUDE_DIRS})

add_executable(dev_zone ./dev_zone.cpp)
target_link_libraries(dev_zone ${PROJECT_NAME} raylib mooncake_log lvgl lvgl_examples lvgl_demos ${SDL2_LIBRARIES})

add_executable(ui_hal ./basic/ui_hal.cpp)
target_link_libraries(ui_hal ${PROJECT_NAME} raylib mooncake_log)

add_executable(animate ./basic/animate.cpp)
target_link_libraries(animate ${PROJECT_NAME} raylib mooncake_log)

add_executable(animate_value ./basic/animate_value.cpp)
target_link_libraries(animate_value ${PROJECT_NAME} raylib mooncake_log)

add_executable(animate_value_options ./basic/animate_value_options.cpp)
target_link_libraries(animate_value_options ${PROJECT_NAME} raylib mooncake_log)

add_executable(basic_animations ./basic/basic_animations.cpp)
target_link_libraries(basic_animations ${PROJECT_NAME} mooncake_log lvgl ${SDL2_LIBRARIES})

add_executable(multi_cursor ./basic/multi_cursor.cpp)
target_link_libraries(multi_cursor ${PROJECT_NAME} raylib mooncake_log)

add_executable(bubbles ./basic/bubbles.cpp)
target_link_libraries(bubbles ${PROJECT_NAME} raylib mooncake_log)

add_executable(event_queue ./event/event_queue.cpp)
target_link_libraries(event_queue ${PROJECT_NAME} pthread)

add_executable(signal ./event/signal.cpp)
target_link_libraries(signal ${PROJECT_NAME} pthread)

add_executable(number_flow ./smooth_lvgl/number_flow.cpp)
target_link_libraries(number_flow ${PROJECT_NAME} mooncake_log lvgl ${SDL2_LIBRARIES})

add_executable(lvgl_cpp ./smooth_lvgl/lvgl_cpp.cpp)
target_link_libraries(lvgl_cpp ${PROJECT_NAME} mooncake_log lvgl ${SDL2_LIBRARIES})
