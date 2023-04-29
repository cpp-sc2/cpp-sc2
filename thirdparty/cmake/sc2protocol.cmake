message(STATUS "FetchContent: protocol")

FetchContent_Declare(
    sc2protocol
    GIT_REPOSITORY https://github.com/Blizzard/s2client-proto.git
    GIT_TAG bb587ce9acb37b776b516cdc1529934341426580
)
FetchContent_MakeAvailable(sc2protocol)
