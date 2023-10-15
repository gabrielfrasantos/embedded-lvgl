add_library(embedded_lvgl.interfaces ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(embedded_lvgl.interfaces PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(embedded_lvgl.interfaces PUBLIC
    infra.util
    infra.stream
    infra.timer
    lvgl::lvgl
)

target_sources(embedded_lvgl.interfaces PRIVATE
    Controller.cpp
    Controller.hpp
)
