cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wextra -pedantic)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")
set(BUILD_SHARED_LIBS ON)

include_directories(${CMAKE_SOURCE_DIR})

set(LOCAL_ROOT $ENV{HOME}/.local)
set(LOCAL_INCLUDE_DIR ${LOCAL_ROOT}/include)
set(LOCAL_LIBRARY_DIR ${LOCAL_ROOT}/lib)

set(BOOST_ROOT ${LOCAL_ROOT})
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

project(using_cpp CXX)

add_subdirectory(entities)
add_subdirectory(errors)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} entities errors)