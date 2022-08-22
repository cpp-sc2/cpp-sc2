message(STATUS "FetchContent: SDL")

# Disabled builds
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL2_DISABLE_UNINSTALL ON CACHE BOOL "" FORCE)
set(SDL2_DISABLE_SDL2MAIN ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG bdc7f958fda50305744dcefdccac29373da97d01
)
FetchContent_MakeAvailable(sdl)

# IDE folders
set_target_properties(SDL2-static PROPERTIES FOLDER contrib)
set_target_properties(sdl_headers_copy PROPERTIES FOLDER contrib)

target_compile_definitions(SDL2-static PRIVATE -DHAVE_LIBC)
