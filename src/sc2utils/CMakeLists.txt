file(GLOB sources_utils "*.cpp" "*.cc" "${PROJECT_SOURCE_DIR}/include/sc2utils/*.h")

add_library(sc2utils ${sources_utils})

target_include_directories(sc2utils PRIVATE "${PROJECT_SOURCE_DIR}/include")

set_target_properties(sc2utils PROPERTIES DEBUG_POSTFIX "d")

if (MSVC)
    set_target_properties(sc2utils PROPERTIES COMPILE_FLAGS "/W3 /WX-")
endif (MSVC)

if (APPLE)
    target_link_libraries(sc2utils "-framework Carbon")
endif ()
