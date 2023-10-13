message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG c04df4adbe274858a4eb8417175ee32ad02fd609
)
FetchContent_MakeAvailable(sc2protocol)
