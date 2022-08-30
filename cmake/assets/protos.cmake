message(STATUS "FetchContent: generated protos for Windows")

FetchContent_Declare(
    protos
    URL https://storage.yandexcloud.net/cpp-sc2/wsl2/generated-s2clientprotocol-db14236-protobuf-1a74ba4.zip
    URL_HASH MD5=346e3d8127f2da6cea4900465183314b
)
FetchContent_MakeAvailable(protos)
