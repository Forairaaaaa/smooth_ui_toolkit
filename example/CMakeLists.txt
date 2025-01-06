# Dependencies
add_subdirectory(dependencies/raylib)
set(MOONCAKE_LOG_BUILD_EXAMPLE OFF)
add_subdirectory(dependencies/mooncake_log)

# Basic
add_executable(basic ./basic.cpp)
target_link_libraries(basic ${PROJECT_NAME} raylib mooncake_log)