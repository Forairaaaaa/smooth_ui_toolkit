# Basic CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Files
file(GLOB_RECURSE SMOOTH_UI_TOOLKIT_SRCS
    src/*.cpp
)
set(SMOOTH_UI_TOOLKIT_INCS
    src/
)

# IDF component
if (ESP_PLATFORM)

idf_component_register(
    SRCS ${SMOOTH_UI_TOOLKIT_SRCS}
    INCLUDE_DIRS ${SMOOTH_UI_TOOLKIT_INCS}
)

else()

#  Build library
add_library(smooth_ui_toolkit ${SMOOTH_UI_TOOLKIT_SRCS})
# Include
target_include_directories(smooth_ui_toolkit PUBLIC ${SMOOTH_UI_TOOLKIT_INCS})

endif()
