set(sc2utils_sources
    sc2_arg_parser.cc
    sc2_manage_process.cc
    sc2_property_reader.cc
    sc2_scan_directory.cc)

set(header_path "${PROJECT_SOURCE_DIR}/include/sc2utils/")
set(sc2utils_headers
    ${header_path}/sc2_arg_parser.h
    ${header_path}/sc2_manage_process.h
    ${header_path}/sc2_property_reader.h
    ${header_path}/sc2_scan_directory.h
    ${header_path}/sc2_simple_serialization.h)

add_library(sc2utils STATIC ${sc2utils_sources} ${sc2utils_headers})

target_include_directories(sc2utils PRIVATE "${PROJECT_SOURCE_DIR}/include")

if (MSVC)
    target_compile_options(sc2utils PRIVATE /W3 /WX-)
endif (MSVC)

if (APPLE)
    target_link_libraries(sc2utils "-framework Carbon")
endif ()
