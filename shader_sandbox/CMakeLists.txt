cmake_minimum_required(VERSION 3.27)
project(STRLShaderSandbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLShaderSandbox src/main.cpp
        src/scenes/ShaderSandboxScene.cpp
        src/scenes/ShaderSandboxScene.h)

target_link_libraries(STRLShaderSandbox STRLEngine)
target_include_directories(STRLShaderSandbox PRIVATE STRLEngine)

add_custom_target(copy_resources_shader_sandbox
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(STRLShaderSandbox copy_resources_shader_sandbox)