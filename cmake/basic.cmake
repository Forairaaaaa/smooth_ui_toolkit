project(smooth_ui_toolkit)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0077 NEW)

option(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL "Enable default HAL implementation using chrono/thread" ON)
if(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL)
    add_compile_definitions(SMOOTH_UI_TOOLKIT_ENABLE_DEFAULT_HAL)
endif()

# Src files
file(GLOB_RECURSE SMOOTH_UI_TOOLKIT_SRCS
    ${SMOOTH_UI_TOOLKIT_ROOT_DIR}/src/*.c
    ${SMOOTH_UI_TOOLKIT_ROOT_DIR}/src/*.cc
    ${SMOOTH_UI_TOOLKIT_ROOT_DIR}/src/*.cpp
)
# Include
set(SMOOTH_UI_TOOLKIT_INCS
    ${SMOOTH_UI_TOOLKIT_ROOT_DIR}/src/
    ${SMOOTH_UI_TOOLKIT_ROOT_DIR}/src/lvgl/
)


add_library(${PROJECT_NAME} ${SMOOTH_UI_TOOLKIT_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SMOOTH_UI_TOOLKIT_INCS})


# Example
option(SMOOTH_UI_TOOLKIT_BUILD_EXAMPLE "Build example" ON)
if(SMOOTH_UI_TOOLKIT_BUILD_EXAMPLE)
    add_subdirectory(./example/)
endif()


# CTest
option(SMOOTH_UI_TOOLKIT_BUILD_TEST "Build test" ON)
if(SMOOTH_UI_TOOLKIT_BUILD_TEST)
    add_subdirectory(./test/)
    enable_testing()
    add_test(ringbuffer test/ringbuffer_test)
endif()