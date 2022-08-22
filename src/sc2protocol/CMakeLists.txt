set(proto_files
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/common.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/data.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/debug.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/error.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/query.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/raw.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/sc2api.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/score.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/spatial.proto"
    "${sc2protocol_SOURCE_DIR}/s2clientprotocol/ui.proto")

# Create the output directory for generated protos.
set(proto_generation_dir "${PROJECT_BINARY_DIR}/generated/s2clientprotocol")
file(MAKE_DIRECTORY "${proto_generation_dir}")

foreach(proto ${proto_files})
    get_filename_component(proto_name ${proto} NAME_WE)
    list(APPEND proto_src
            "${proto_generation_dir}/${proto_name}.pb.cc"
            "${proto_generation_dir}/${proto_name}.pb.h")
endforeach()

add_library(sc2protocol STATIC ${proto_src})

target_include_directories(sc2protocol SYSTEM PUBLIC "${PROJECT_BINARY_DIR}/generated")

target_link_libraries(sc2protocol PUBLIC libprotobuf)

if (MSVC)
    target_compile_options(sc2protocol PRIVATE /W0)
endif (MSVC)

# Copy precompiled protos to the generated directory
if (WSL2_CROSS_COMPILE)
    foreach (proto ${proto_files})
        get_filename_component(proto_name ${proto} NAME_WE)
        file(
            COPY
                "${protos_SOURCE_DIR}/${proto_name}.pb.h"
                "${protos_SOURCE_DIR}/${proto_name}.pb.cc"
            DESTINATION
                "${proto_generation_dir}")
    endforeach ()
# Compile protos with protoc
else ()
    foreach (proto ${proto_files})
        get_filename_component(proto_name_we ${proto} NAME_WE)
        set(protoc_out_cc "${proto_generation_dir}/${proto_name_we}.pb.cc")
        set(protoc_out_h "${proto_generation_dir}/${proto_name_we}.pb.h")

        add_custom_command(
            OUTPUT
                "${protoc_out_cc}"
                "${protoc_out_h}"
            COMMAND
                "${PROJECT_BINARY_DIR}/bin/protoc"
                "-I=${sc2protocol_SOURCE_DIR}"
                "--cpp_out=${PROJECT_BINARY_DIR}/generated"
                "${proto}"
            DEPENDS protoc
            VERBATIM
        )
    endforeach()
endif ()
