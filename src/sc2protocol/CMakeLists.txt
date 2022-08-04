# Gather the protos.
file(GLOB proto_files "${PROJECT_SOURCE_DIR}/protocol/s2clientprotocol/*.proto")

if ("${proto_files}" STREQUAL "")
    message(FATAL_ERROR "Missing root protocol submodule.\nRemove your protocol directory and run:\ngit submodule update --recursive --init")
endif ()

# Create the output directory for generated protos.
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/generated/s2clientprotocol)

foreach(proto ${proto_files})
    get_filename_component(proto_name ${proto} NAME_WE)
    list(APPEND proto_src ${PROJECT_BINARY_DIR}/generated/s2clientprotocol/${proto_name}.pb.h ${PROJECT_BINARY_DIR}/generated/s2clientprotocol/${proto_name}.pb.cc)
endforeach()

add_library(sc2protocol ${proto_src} ${proto_files})
add_dependencies(sc2protocol protoc)

target_include_directories(sc2protocol SYSTEM PUBLIC "${PROJECT_BINARY_DIR}/generated")

target_link_libraries(sc2protocol PUBLIC libprotobuf)

set_target_properties(sc2protocol PROPERTIES DEBUG_POSTFIX "d")

foreach (proto ${proto_files})
    get_filename_component(proto_name ${proto} NAME)
    get_filename_component(proto_name_we ${proto} NAME_WE)
    set(outputCC ${PROJECT_BINARY_DIR}/generated/s2clientprotocol/${proto_name_we}.pb.cc)
    set(outputH ${PROJECT_BINARY_DIR}/generated/s2clientprotocol/${proto_name_we}.pb.h)

    add_custom_command(
        DEPENDS protoc
        COMMAND ${PROJECT_BINARY_DIR}/bin/protoc -I=${PROJECT_SOURCE_DIR}/protocol/ --cpp_out=${PROJECT_BINARY_DIR}/generated ${proto}
        OUTPUT ${outputCC} ${outputH}
    )
endforeach()

if (MSVC)
    set_target_properties(sc2protocol PROPERTIES COMPILE_FLAGS "/W0")
endif (MSVC)
