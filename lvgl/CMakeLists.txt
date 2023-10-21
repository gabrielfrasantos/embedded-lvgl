cmake_minimum_required(VERSION 3.24)

if (NOT DEFINED EMBEDDED_LVGL_LV_CONF_PATH)
    set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/configuration/lv_conf.h CACHE STRING "" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl
    GIT_TAG        v8.3.10
)

FetchContent_MakeAvailable(lvgl)
target_compile_definitions(lvgl PUBLIC -DLV_CONF_PATH=${LV_CONF_PATH})

add_subdirectory(interfaces)
add_subdirectory(core)
add_subdirectory(widgets)