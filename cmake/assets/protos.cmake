message(STATUS "FetchContent: generated protos for Windows")

FetchContent_Declare(
    protos
    URL https://storage.yandexcloud.net/cpp-sc2/wsl2/generated-s2clientprotocol-998ca3b-protobuf-2c35697b.zip
    URL_HASH MD5=1eb0a4e762d366dfc052194b691fc0ab
)
FetchContent_MakeAvailable(protos)
