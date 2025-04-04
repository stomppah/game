include(FetchContent)

FetchContent_MakeAvailable(
    googletest
)

include(GoogleTest)

mark_as_advanced(BUILD_GMOCK BUILD_GTEST gtest_hide_internal_symbols)

add_executable(unit_tests
    vector3_tests.cpp
)

target_compile_features(unit_tests PRIVATE cxx_std_20)

target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(unit_tests gmock_main)
gtest_discover_tests(unit_tests DISCOVERY_MODE PRE_TEST)