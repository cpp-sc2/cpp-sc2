message(STATUS "FetchContent: civetweb")

# Disable builds
set(CIVETWEB_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(CIVETWEB_ENABLE_SERVER_EXECUTABLE OFF CACHE BOOL "" FORCE)

# Disable ASAN debug
set(CIVETWEB_ENABLE_ASAN OFF CACHE BOOL "" FORCE)

# Enable websocket connections
set(CIVETWEB_ENABLE_WEBSOCKETS ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    civetweb
    GIT_REPOSITORY https://github.com/cpp-sc2/civetweb.git
    GIT_TAG d814cc25f56ab9468863e27410a33146301594f6
)
FetchContent_MakeAvailable(civetweb)

set_target_properties(civetweb-c-library PROPERTIES FOLDER contrib)

target_compile_options(civetweb-c-library PUBLIC -DUSE_IPV6=1)
