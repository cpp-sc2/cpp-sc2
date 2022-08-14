add_subdirectory(sc2api)
add_subdirectory(sc2lib)
add_subdirectory(sc2utils)
add_subdirectory(sc2protocol)

if (BUILD_SC2_RENDERER)
    add_subdirectory(sc2renderer)
endif ()

add_library(cpp_sc2 INTERFACE)

target_link_libraries(cpp_sc2
    INTERFACE
        sc2api
        sc2lib
        sc2utils)
