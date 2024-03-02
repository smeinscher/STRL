cmake_minimum_required(VERSION 3.27)
project(STRLPong)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLPong src/main.cpp
        src/scripts/PongBall.cpp
        src/scripts/PongBall.h
        src/scripts/Opponent.cpp
        src/scripts/Opponent.h
        src/scripts/Player.cpp
        src/scripts/Player.h
        src/scenes/Pong.cpp
        src/scenes/Pong.h
)

target_link_libraries(STRLPong STRLEngine)
target_include_directories(STRLPong PRIVATE STRLEngine)

add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(STRLPong copy_resources)