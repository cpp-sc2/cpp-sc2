message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG db142363be5e4da522879b8b43db69c6313bcd57
)
FetchContent_MakeAvailable(sc2protocol)
