add_executable(embedded_lvgl.examples.widgets)

target_include_directories(embedded_lvgl.examples.widgets PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../..>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(embedded_lvgl.examples.widgets PUBLIC
    embedded_lvgl.widgets
    infra.util
    services.util
    hal_tiva.instantiations
    hal_tiva.tiva
)

target_sources(embedded_lvgl.examples.widgets PRIVATE
    Main.cpp
)

hal_ti_target_default_linker_scripts(embedded_lvgl.examples.widgets)
hal_ti_target_default_init(embedded_lvgl.examples.widgets)

emil_generate_artifacts(TARGET embedded_lvgl.examples.widgets LST MAP BIN HEX)