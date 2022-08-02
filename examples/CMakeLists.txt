# Function to generate an example project with extra libraries
function (example_project_extra project_name source_code extra_libs)
    message(VERBOSE "Adding new example project ${project_name}, sources: ${source_code}, extra_libs: ${extra_libs}")
    file (GLOB example_project_sources ${source_code} "common/*.h" "common/*.cc")
    add_executable(${project_name} ${example_project_sources})

    target_include_directories(${project_name} PRIVATE "${PROJECT_SOURCE_DIR}/examples/common")

    set_target_properties(${project_name} PROPERTIES FOLDER examples)

	if (MSCV AND (NOT (MSVC_VERSION LESS 1910)))
		target_link_libraries(${project_name} PRIVATE legacy_stdio_definitions)
	endif ()

    target_link_libraries(${project_name} PRIVATE cpp_sc2 ${extra_libs})
endfunction ()

# Function to generate a simple example project
function (example_project project_name source_code)
    example_project_extra(${project_name} ${source_code} "")
endfunction ()

example_project(bot_simple "bot_simple.cc")
example_project(echo_actions "echo_actions.cc")
example_project(replay "replay.cc")
example_project(tutorial "tutorial.cc")
example_project(bot_micro "bot_micro.cc")
example_project(bot_mp "bot_mp.cc")
example_project(intermediate_bot "intermediate_bot.cc")
example_project(annoying_helper "annoying_helper.cc")
example_project(proxy "proxy.cc")
example_project(save_load "save_load.cc")

if (BUILD_SC2_RENDERER)
    example_project_extra(feature_layers "feature_layers.cc" sc2renderer)
    example_project_extra(rendered "rendered.cc" sc2renderer)
endif ()

