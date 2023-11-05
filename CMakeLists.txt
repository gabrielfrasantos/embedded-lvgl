cmake_minimum_required(VERSION 3.24)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(EMBEDDED_LVGL_STANDALONE On)
endif()

if (EMBEDDED_LVGL_STANDALONE)
    include(FetchContent)

    FetchContent_Declare(
        emil
        GIT_REPOSITORY https://github.com/gabrielfrasantos/embedded-infra-lib.git
        GIT_TAG        230ca4750f210485ff99b3fea1f9161948fc4d26 # Unreleased
    )

    FetchContent_MakeAvailable(emil)

    if (TARGET_MCU_VENDOR STREQUAL ti)
        FetchContent_Declare(
            halst
            GIT_REPOSITORY https://github.com/gabrielfrasantos/embedded-hal-ti
            GIT_TAG        ba279cc0cb201f1b4ce1082c0215fa3880883c87 # unreleased
        )

        FetchContent_MakeAvailable(halst)
    endif()
endif()

option(CMAKE_COMPILE_WARNING_AS_ERROR "Enable warnings-as-error" ON)
option(EMBEDDED_LVGL_BUILD_EXAMPLES "Enable build of the examples" OFF)

project(embedded-lvgl LANGUAGES C CXX ASM VERSION 0.0.1) # x-release-please-version

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(FetchContent)

FetchContent_Declare(
    lvgl
    GIT_REPOSITORY https://github.com/lvgl/lvgl
    GIT_TAG        v8.3.10
)

FetchContent_MakeAvailable(lvgl)

set_directory_properties(PROPERTY USE_FOLDERS ON)

# When building HalSt by itself do not exclude any targets from all
# Libraries will only be excluded from all when HalSt is a consumed as a dependency.
if (EMBEDDED_LVGL_STANDALONE AND NOT EMIL_HOST_BUILD)
    set(EMBEDDED_LVGL_EXCLUDE_FROM_ALL "")
else()
    set(EMBEDDED_LVGL_EXCLUDE_FROM_ALL "EXCLUDE_FROM_ALL")
endif()

add_subdirectory(lvgl)

if (EMBEDDED_LVGL_STANDALONE)
    add_subdirectory(examples)
endif()

emil_clangformat_directories(lvgl DIRECTORIES .)

if (EMBEDDED_LVGL_STANDALONE)
    emil_folderize_all_targets()
endif()
