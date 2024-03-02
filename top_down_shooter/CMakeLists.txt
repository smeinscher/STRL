cmake_minimum_required(VERSION 3.27)
project(STRLTopDownShooter)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLTopDownShooter src/main.cpp
        src/scripts/Player.cpp
        src/scripts/Player.h
        src/scenes/GameScene.cpp
        src/scenes/GameScene.h
)

target_link_libraries(STRLTopDownShooter STRLEngine)
target_include_directories(STRLTopDownShooter PRIVATE STRLEngine)

add_custom_target(copy_resources_tds
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(STRLTopDownShooter copy_resources_tds)