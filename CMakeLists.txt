cmake_minimum_required(VERSION 3.15)

project(using_cpp)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wextra -pedantic)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")
set(BUILD_SHARED_LIBS ON)

find_package(Boost REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(entities)
add_subdirectory(errors)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} entities errors)