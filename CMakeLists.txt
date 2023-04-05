cmake_minimum_required(VERSION 3.24)

project(class-dump LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v4.0.0"
        GIT_SHALLOW ON
        )

FetchContent_MakeAvailable(GSL)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)

if (APPLE)
    enable_testing()
    add_subdirectory(test)
endif ()