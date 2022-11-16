message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 18996243c8c51e431fae177a7f3d0a65d12e9365
)
FetchContent_MakeAvailable(sc2protocol)
