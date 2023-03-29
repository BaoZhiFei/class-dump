cmake_minimum_required(VERSION 3.24)

project(class-dump)

set(CMAKE_CXX_STANDARD 23)

add_executable(class-dump main.cpp)

if(APPLE)
    enable_testing()
    add_subdirectory(test)
endif()