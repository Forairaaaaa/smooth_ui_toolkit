# Dependencies
add_subdirectory(dependencies/raylib)
set(MOONCAKE_LOG_BUILD_EXAMPLE OFF)
add_subdirectory(dependencies/mooncake_log)

add_executable(dev_zone ./dev_zone.cpp)
target_link_libraries(dev_zone ${PROJECT_NAME} raylib mooncake_log)

add_executable(ui_hal ./basic/ui_hal.cpp)
target_link_libraries(ui_hal ${PROJECT_NAME} raylib mooncake_log)

add_executable(animate ./basic/animate.cpp)
target_link_libraries(animate ${PROJECT_NAME} raylib mooncake_log)

add_executable(animate_value ./basic/animate_value.cpp)
target_link_libraries(animate_value ${PROJECT_NAME} raylib mooncake_log)
