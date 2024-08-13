message(STATUS "FetchContent: protobuf")

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Cross compiling causes protoc to be built for target (Windows)
if (WSL2_CROSS_COMPILE)
    set(protobuf_BUILD_PROTOC_BINARIES OFF CACHE BOOL "" FORCE)
endif ()

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v3.23.4
)
FetchContent_MakeAvailable(protobuf)

if (WSL2_CROSS_COMPILE)
    message(STATUS "FetchContent: pre-compiled protoc binary for WSL")
    # This must version match protobuf GIT_TAG above, or will generate runtime errors.
    FetchContent_Declare(
        protos
        URL https://github.com/protocolbuffers/protobuf/releases/download/v23.4/protoc-23.4-linux-x86_64.zip
    )
    FetchContent_MakeAvailable(protos)
    set(protobuf_targets libprotobuf libprotobuf-lite libprotoc)

else ()
    set(protobuf_targets libprotobuf libprotobuf-lite libprotoc protoc)
endif ()

foreach (target IN LISTS protobuf_targets)
    if (TARGET ${target})
        set_target_properties(${target} PROPERTIES FOLDER contrib)
    endif ()

    if (MSVC)
        target_compile_options(${target} PRIVATE /W0)
    endif ()
endforeach ()
