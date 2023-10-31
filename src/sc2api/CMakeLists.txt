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

set(header_path "${PROJECT_SOURCE_DIR}/include/sc2api/")
set(sc2api_headers
    ${header_path}/sc2_action.h
    ${header_path}/sc2_agent.h
    ${header_path}/sc2_api.h
    ${header_path}/sc2_args.h
    ${header_path}/sc2_client.h
    ${header_path}/sc2_common.h
    ${header_path}/sc2_connection.h
    ${header_path}/sc2_control_interfaces.h
    ${header_path}/sc2_coordinator.h
    ${header_path}/sc2_data.h
    ${header_path}/sc2_errors.h
    ${header_path}/sc2_gametypes.h
    ${header_path}/sc2_game_settings.h
    ${header_path}/sc2_interfaces.h
    ${header_path}/sc2_map_info.h
    ${header_path}/sc2_proto_interface.h
    ${header_path}/sc2_proto_to_pods.h
    ${header_path}/sc2_replay_observer.h
    ${header_path}/sc2_score.h
    ${header_path}/sc2_server.h
    ${header_path}/sc2_typeenums.h
    ${header_path}/sc2_types.h
    ${header_path}/sc2_unit.h
    ${header_path}/sc2_unit_filters.h
    "${header_path}/typeids/sc2_${SC2_VERSION}_typeenums.h")

add_library(sc2api STATIC ${sc2api_sources} ${sc2api_headers})

target_include_directories(sc2api PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(sc2api SYSTEM PUBLIC "${civetweb_SOURCE_DIR}/include")

target_link_libraries(sc2api PUBLIC sc2protocol civetweb-c-library)

if (MSVC)
    target_compile_options(sc2api PRIVATE /W4 /WX-)
endif ()
