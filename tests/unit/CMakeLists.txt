message(STATUS "FetchContent: doctest")

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(cpp_sc2_unit_tests
    test_main.cc
    test_ability_data.cc
    test_score_details.cc
)

target_include_directories(cpp_sc2_unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(cpp_sc2_unit_tests PRIVATE
    sc2api
    sc2lib
    doctest::doctest
)

set_target_properties(cpp_sc2_unit_tests PROPERTIES FOLDER tests)
