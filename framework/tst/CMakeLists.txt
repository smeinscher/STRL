cmake_minimum_required(VERSION 3.27)
project(STRLTest)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_executable(STRLTest src/main.cpp
        src/renderer/OpenGLRenderer_tests.cpp
        src/platform/GLFWPlatform_tests.cpp)
target_link_libraries(STRLTest
        PUBLIC
            STRLFramework
        PRIVATE
            GTest::gtest_main
)
target_include_directories(STRLTest PRIVATE STRLFramework)

add_subdirectory(external)
include(GoogleTest)
gtest_discover_tests(STRLTest)