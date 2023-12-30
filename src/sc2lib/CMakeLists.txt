set(sc2lib_sources
    sc2_lib.h
    sc2_search.cc
    sc2_search.h
    sc2_utils.cc
    sc2_utils.h
)

add_library(sc2lib STATIC ${sc2lib_sources})

target_link_libraries(sc2lib PRIVATE sc2api)

if (MSVC)
    target_compile_options(sc2lib PRIVATE /W4 /WX-)
endif ()
