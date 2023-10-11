message(STATUS "FetchContent: civetweb")

# Disable builds
set(CIVETWEB_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CIVETWEB_ENABLE_SERVER_EXECUTABLE OFF CACHE BOOL "" FORCE)

# Disable ASAN debug
set(CIVETWEB_ENABLE_ASAN OFF CACHE BOOL "" FORCE)

# Enable websocket connections
set(CIVETWEB_ENABLE_WEBSOCKETS ON CACHE BOOL "" FORCE)

# Disable IPv6 as we use only IPv4
set(CIVETWEB_ENABLE_IPV6 OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    civetweb
    GIT_REPOSITORY https://github.com/cpp-sc2/civetweb.git
    GIT_TAG 61fc8f811acb3da60d313d5459aa93c9e85fe32c
)
FetchContent_MakeAvailable(civetweb)

set_target_properties(civetweb-c-library PROPERTIES FOLDER contrib)

target_compile_options(civetweb-c-library PUBLIC -DUSE_IPV6=1)
