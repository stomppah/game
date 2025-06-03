cmake_minimum_required(VERSION 3.22) 

project(
    game
    VERSION "0.0.1"
    DESCRIPTION "jfk jr woz 'ere"
    LANGUAGES C CXX
)

enable_testing()
include(CTest)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_subdirectory(tests)
