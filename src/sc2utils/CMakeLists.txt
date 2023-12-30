set(sc2utils_sources
    dirent.h
    sc2_arg_parser.cc
    sc2_arg_parser.h
    sc2_manage_process.cc
    sc2_manage_process.h
    sc2_property_reader.cc
    sc2_property_reader.h
    sc2_scan_directory.cc
    sc2_scan_directory.h
    sc2_simple_serialization.h
)

add_library(sc2utils STATIC ${sc2utils_sources})

if (MSVC)
    target_compile_options(sc2utils PRIVATE /W3 /WX-)
endif (MSVC)

if (APPLE)
    target_link_libraries(sc2utils "-framework Carbon")
endif ()
