message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG bff45dae1fc685e6acbaae084670afb7d1c0832c
    GIT_PROGRESS TRUE
    # Patch to apply:
    # - Packed Encoding for Repeated Fields
    # - Arena Allocation
    PATCH_COMMAND git apply "${CMAKE_CURRENT_LIST_DIR}/sc2protocol-arena-packing.patch"
)
FetchContent_MakeAvailable(sc2protocol)
