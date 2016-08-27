cmake_minimum_required (VERSION 3.5.1)
project (tinyemu)

set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-modules)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O0")

add_subdirectory (source-code)
