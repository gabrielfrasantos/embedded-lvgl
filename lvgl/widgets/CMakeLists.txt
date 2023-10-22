add_library(embedded_lvgl.widgets ${EMIL_EXCLUDE_FROM_ALL} STATIC)

target_include_directories(embedded_lvgl.widgets PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(embedded_lvgl.widgets PUBLIC
    infra.util
    lvgl::lvgl
    embedded_lvgl.core
)

target_sources(embedded_lvgl.widgets PRIVATE
    Button.cpp
    Button.hpp
    Label.cpp
    Label.hpp
    Led.cpp
    Led.hpp
)
