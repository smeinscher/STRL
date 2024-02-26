cmake_minimum_required(VERSION 3.27)
project(STRL)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(CMAKE_ADDITIONAL_FLAGS "-static-libstdc++ -static-libgcc -static")
endif (WIN32)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 ${CMAKE_ADDITIONAL_FLAGS}")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 ${CMAKE_ADDITIONAL_FLAGS}")
endif()

add_subdirectory(app)
add_subdirectory(engine)
