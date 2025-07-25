cmake_minimum_required(VERSION 3.14)

project(smooth_ui_toolkit)

set(SMOOTH_UI_TOOLKIT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

if (ESP_PLATFORM)
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/esp_idf.cmake)
else()
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/basic.cmake)
endif()