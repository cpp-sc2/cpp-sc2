message(STATUS "FetchContent: protobuf")

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG 1a74ba4cb4c2faee902e9088281d824385ba2bc6
)
FetchContent_MakeAvailable(protobuf)

# Location of the protobuf project top level CMakeLists.txt
add_subdirectory("${protobuf_SOURCE_DIR}/cmake" "${protobuf_BINARY_DIR}")

set(protobuf_targets libprotobuf libprotobuf-lite libprotoc protoc)

foreach (target IN LISTS protobuf_targets)
    if (TARGET ${target})
        set_target_properties(${target} PROPERTIES FOLDER contrib)
    endif ()

    if (MSVC)
        target_compile_options(${target} PRIVATE /W0)
    endif ()
endforeach ()
