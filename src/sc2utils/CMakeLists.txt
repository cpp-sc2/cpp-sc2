set(sc2utils_sources
    sc2_arg_parser.cc
    sc2_manage_process.cc
    sc2_property_reader.cc
    sc2_scan_directory.cc)

add_library(sc2utils STATIC ${sc2utils_sources})

target_include_directories(sc2utils PRIVATE "${PROJECT_SOURCE_DIR}/include")

if (MSVC)
    target_compile_options(sc2utils PRIVATE /W3 /WX-)
endif (MSVC)

if (APPLE)
    target_link_libraries(sc2utils "-framework Carbon")
endif ()
