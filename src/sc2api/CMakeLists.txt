# Inject sources specific for particular version of the game client
file(WRITE "${PROJECT_SOURCE_DIR}/include/sc2api/sc2_typeenums.h"
"#pragma once

#include \"typeids/sc2_${SC2_VERSION}_typeenums.h\"
"
)

set(sc2api_sources
    sc2_action.cc
    sc2_agent.cc
    sc2_args.cc
    sc2_client.cc
    sc2_common.cc
    sc2_connection.cc
    sc2_coordinator.cc
    sc2_data.cc
    sc2_game_settings.cc
    sc2_map_info.cpp
    sc2_proto_interface.cc
    sc2_proto_to_pods.cc
    sc2_replay_observer.cc
    sc2_score.cc
    sc2_server.cc
    sc2_unit_filters.cc
    sc2_unit.cc
    "typeids/sc2_${SC2_VERSION}_typeenums.cpp")

add_library(sc2api STATIC ${sc2api_sources})

target_include_directories(sc2api PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(sc2api SYSTEM PUBLIC "${civetweb_SOURCE_DIR}/include")

target_link_libraries(sc2api PUBLIC sc2protocol civetweb-c-library)

if (MSVC)
    target_compile_options(sc2api PRIVATE /W4 /WX-)
endif ()
