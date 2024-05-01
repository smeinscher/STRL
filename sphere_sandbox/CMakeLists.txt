cmake_minimum_required(VERSION 3.27)
project(STRLSphereSandbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLSphereSandbox src/main.cpp
        src/scenes/SphereSandboxScene.cpp
        src/scenes/SphereSandboxScene.h
        src/scripts/Unit.cpp
        src/scripts/Unit.h
        src/states/States.cpp
        src/states/States.h
        src/scripts/Formation.cpp
        src/scripts/Formation.h)

target_link_libraries(STRLSphereSandbox STRLFramework)
target_include_directories(STRLSphereSandbox PRIVATE STRLFramework)

add_custom_target(copy_resources_sphere_sandbox
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(STRLSphereSandbox copy_resources_sphere_sandbox)