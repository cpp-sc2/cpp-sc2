# All the source files for the sc2 api
file(GLOB sources_sc2 "*.cpp" "*.cc" "*.h")

# Inject sources specific for particular version of the game client
file(WRITE "${PROJECT_SOURCE_DIR}/include/sc2api/sc2_typeenums.h"
"#pragma once

#include \"typeids/sc2_${SC2_VERSION}_typeenums.h\"
"
)

list(APPEND sources_sc2
    "${PROJECT_SOURCE_DIR}/include/sc2api/sc2_typeenums.h"
    "${PROJECT_SOURCE_DIR}/include/sc2api/typeids/sc2_${SC2_VERSION}_typeenums.h"
    "${PROJECT_SOURCE_DIR}/src/sc2api/typeids/sc2_${SC2_VERSION}_typeenums.cpp"
)

add_library(sc2api ${sources_sc2})

target_include_directories(sc2api
    PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/contrib/civetweb/include"
        "${PROJECT_SOURCE_DIR}/contrib/ipv6-parse")

target_link_libraries(sc2api
    PUBLIC
        sc2protocol
        civetweb-c-library
        ipv6-parse)

set_target_properties(sc2api PROPERTIES DEBUG_POSTFIX "d")

if (MSVC)
    set_target_properties(sc2api PROPERTIES COMPILE_FLAGS "/W4 /WX-")
endif ()
