file(GLOB sources_sc2_lib "*.cpp" "*.cc" "${PROJECT_SOURCE_DIR}/include/sc2lib/*.h")

add_library(sc2lib ${sources_sc2_lib})

target_link_libraries(sc2lib PRIVATE sc2api)

set_target_properties(sc2lib PROPERTIES DEBUG_POSTFIX "d")

if (MSVC)
    set_target_properties(sc2lib PROPERTIES COMPILE_FLAGS "/W4 /WX-")
endif ()
