set(sc2test_sources
    all_tests.cc
    feature_layers_shared.cc
    test_ability_remap.cc
    test_actions.cc
    test_app.cc
    test_feature_layer_mp.cc
    test_feature_layer.cc
    test_framework.cc
    test_movement_combat.cc
    test_multiplayer.cc
    test_observation_interface.cc
    test_performance.cc
    test_restart.cc
    test_snapshots.cc
    test_unit_command_common.cc
    test_unit_command.cc)

add_executable(all_tests ${sc2test_sources})

target_include_directories(all_tests PRIVATE "${PROJECT_SOURCE_DIR}/examples/common")

set_target_properties(all_tests PROPERTIES FOLDER tests)

if (BUILD_SC2_RENDERER)
    target_sources(all_tests PRIVATE test_rendered.cc)
    target_compile_definitions(all_tests PRIVATE -DBUILD_SC2_RENDERER)
endif ()

target_link_libraries(all_tests sc2api sc2lib sc2utils)
