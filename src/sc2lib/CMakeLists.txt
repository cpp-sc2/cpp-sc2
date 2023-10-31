set(sc2lib_sources
    sc2_search.cc
    sc2_utils.cc)

set(header_path "${PROJECT_SOURCE_DIR}/include/sc2lib/")
set(sc2lib_headers
    ${header_path}/sc2_lib.h
    ${header_path}/sc2_search.h
    ${header_path}/sc2_utils.h)

add_library(sc2lib STATIC ${sc2lib_sources} ${sc2lib_headers})

target_link_libraries(sc2lib PRIVATE sc2api)

if (MSVC)
    target_compile_options(sc2lib PRIVATE /W4 /WX-)
endif ()
