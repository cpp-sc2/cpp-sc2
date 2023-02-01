message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG 42f4641080f421119ad8214d8a252b3797c09ca9
)
FetchContent_MakeAvailable(sc2protocol)
