include(FetchContent)

FetchContent_MakeAvailable(
    googletest
)

include(GoogleTest)

mark_as_advanced(BUILD_GMOCK BUILD_GTEST gtest_hide_internal_symbols)

add_executable(unit_tests
    vector3_tests.cpp
    matrix4_tests.cpp
)

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_features(unit_tests PRIVATE cxx_std_23)
target_compile_definitions(unit_tests PRIVATE -DNOMINMAX)
target_compile_options(unit_tests PRIVATE /W4 /WX )# /Debug /Od /Z7

target_link_libraries(unit_tests gmock_main)
add_test(NAME unit_tests COMMAND unit_tests)
