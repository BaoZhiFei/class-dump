cmake_minimum_required(VERSION 3.24)

project(class-dump LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

add_compile_options(-fno-exceptions -fno-rtti -Wall -Wextra -pedantic)

include(FetchContent)

find_package(GSL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)

if (APPLE)
    enable_testing()
    add_subdirectory(test)
endif ()