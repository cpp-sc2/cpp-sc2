message(STATUS "FetchContent: protocol")

set(sc2client-proto_patches
    "${CMAKE_CURRENT_LIST_DIR}/0001-proofread.patch"
    "${CMAKE_CURRENT_LIST_DIR}/0002-proto3.patch"
)
set(patch_command git apply --ignore-whitespace "${sc2client-proto_patches}")

FetchContent_Declare(
    sc2client-proto
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG bff45dae1fc685e6acbaae084670afb7d1c0832c
    GIT_PROGRESS TRUE
    PATCH_COMMAND ${patch_command}
    UPDATE_DISCONNECTED TRUE
)
FetchContent_MakeAvailable(sc2client-proto)
