cmake_minimum_required(VERSION 3.27)
project(STRLApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLApp src/main.cpp
        src/scripts/PongBall.cpp
        src/scripts/PongBall.h
        src/scripts/Opponent.cpp
        src/scripts/Opponent.h
        src/scripts/Player.cpp
        src/scripts/Player.h
        src/scripts/Misc.cpp
        src/scripts/Misc.h)

target_link_libraries(STRLApp STRLEngine)
target_include_directories(STRLApp PRIVATE PongEngine)

add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(STRLApp copy_resources)