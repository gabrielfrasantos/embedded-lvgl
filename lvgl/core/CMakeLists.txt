add_library(embedded_lvgl.core ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(embedded_lvgl.core PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(embedded_lvgl.core PUBLIC
    infra.util
    lvgl::lvgl
)

target_sources(embedded_lvgl.core PRIVATE
    Event.hpp
    Event.cpp
    Object.cpp
    Object.hpp
    Position.cpp
    Position.hpp
    Screen.cpp
    Screen.hpp
    Scroll.cpp
    Scroll.hpp
)
