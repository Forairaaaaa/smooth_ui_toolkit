cmake_minimum_required(VERSION 3.14)

project(smooth_ui_toolkit)

set(SMOOTH_UI_TOOLKIT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

option(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL "Enable default HAL implementation using chrono/thread" ON)
if(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL)
    add_compile_definitions(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL)
endif()

if (ESP_PLATFORM)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/esp_idf.cmake)
else()
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/basic.cmake)
endif()