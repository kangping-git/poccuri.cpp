cmake_minimum_required(VERSION 3.15)

project(PoccuriCpp
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(PoccuriCpp "src/main.cpp" ${SOURCES})

target_include_directories(PoccuriCpp PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)