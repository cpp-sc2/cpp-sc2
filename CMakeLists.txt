cmake_minimum_required(VERSION 3.15)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW)
endif ()

# Skip generating proto files with Protobuf compiler and use prebuilt files
# Will still build Protobuf as libprotobuf is required for linking
option(WSL2_CROSS_COMPILE "Building on WSL2 for Windows" OFF)

# Downstream projects including cpp-sc2 as a dependency must set toolchain the
# toolchain file
if (DEFINED CMAKE_TOOLCHAIN_FILE)
    message(DEBUG "Toolchain file already set to ${CMAKE_TOOLCHAIN_FILE}")
elseif (WSL2_CROSS_COMPILE)
    set(CMAKE_TOOLCHAIN_FILE cmake/toolchain/x86-64-w64-mingw32.cmake)
endif ()

project(cpp-sc2)

include(FetchContent)

option(BUILD_SC2_RENDERER "Build SC2 Renderer library" ON)
option(BUILD_API_EXAMPLES "Build Examples" ON)
option(BUILD_API_TESTS "Build Tests" ON)

set(SC2_VERSION "5.0.12" CACHE STRING "Version of the target StarCraft II client")
message(STATUS "Target SC2 version: ${SC2_VERSION}")

# Use bin as the directory for all executables.
# This will make protoc easy to find.
set(CPP_SC2_BUILD_DIR "${PROJECT_BINARY_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")
set(LIBRARY_OUTPUT_PATH "${CPP_SC2_BUILD_DIR}")

# Windows builds subdirectories Debug/Release.
# These variables will overwrite that and put binaries in bin.
set(build_types DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
set(output_types LIBRARY ARCHIVE RUNTIME)

foreach (build IN LISTS build_types)
    foreach (output IN LISTS output_types)
        set(CMAKE_${output}_OUTPUT_DIRECTORY_${build} "${CPP_SC2_BUILD_DIR}")
    endforeach ()
endforeach ()

# All libraries built with debug should be the same postfix
set(LIBRARY_DEBUG_POSTFIX d)
set(CMAKE_DEBUG_POSTFIX ${LIBRARY_DEBUG_POSTFIX})

# External subprojects
list(APPEND CMAKE_MODULE_PATH
    "${PROJECT_SOURCE_DIR}/thirdparty/cmake"
    "${PROJECT_SOURCE_DIR}/cmake/assets")

# Build with c++14 support.
set(CMAKE_CXX_STANDARD 14)

# Allow creating filters for projects in visual studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
    # Setup MSVC parallelized builds
    add_compile_options(/MP)

    # Use statically linked runtime
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
endif ()

if (BUILD_API_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BUILD_API_TESTS)
    add_subdirectory(tests)
endif ()

if (WSL2_CROSS_COMPILE)
    include(protos)
endif ()

# External subproject depedencies
include(civetweb)
include(protobuf)
include(sc2protocol)
if (BUILD_SC2_RENDERER)
    include(SDL)
endif ()

# cpp-sc2 libraries
add_subdirectory(src)
