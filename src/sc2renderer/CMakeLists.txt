file(GLOB sources_renderer "*.cc" "*.h" "${PROJECT_SOURCE_DIR}/include/sc2renderer/*.h")

add_library(sc2renderer ${sources_renderer})

target_include_directories(sc2renderer
    PRIVATE
        "${PROJECT_SOURCE_DIR}/contrib/SDL-mirror/include"
        "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(sc2renderer PRIVATE SDL2-static)

if (MSVC)
    set_target_properties(sc2renderer PROPERTIES COMPILE_FLAGS "/W4 /WX-")
endif()

set_target_properties(sc2renderer PROPERTIES DEBUG_POSTFIX "d")
