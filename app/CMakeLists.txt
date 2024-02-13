cmake_minimum_required(VERSION 3.27)
project(STRLApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(STRLApp src/main.cpp)

target_link_libraries(STRLApp PongEngine)
target_include_directories(STRLApp PRIVATE PongEngine)