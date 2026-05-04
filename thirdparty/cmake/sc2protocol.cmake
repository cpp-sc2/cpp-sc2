message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG bff45dae1fc685e6acbaae084670afb7d1c0832c
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(sc2protocol)
