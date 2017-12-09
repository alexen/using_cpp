cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)
add_definitions(-Wall -Werror -Wextra -pedantic)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")
set(BUILD_SHARED_LIBS ON)

include_directories(${CMAKE_SOURCE_DIR})

set(NAME using_cpp)
add_executable(${NAME}
     main.cpp
)