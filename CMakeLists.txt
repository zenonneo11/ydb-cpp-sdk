cmake_minimum_required(VERSION 3.15)
project(YDB-CPP-SDK LANGUAGES C CXX ASM)

set(BUILD_SHARED_LIBS Off)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS On)

set(YDB_SDK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(YDB_SDK_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${YDB_SDK_BINARY_DIR} ${YDB_SDK_SOURCE_DIR}/cmake)
include_directories(${YDB_SDK_SOURCE_DIR} ${YDB_SDK_SOURCE_DIR}/include ${YDB_SDK_BINARY_DIR})
enable_testing()

include(cmake/common.cmake)
include(cmake/ccache.cmake)
include(cmake/global_flags.cmake)
include(cmake/protobuf.cmake)
include(cmake/global_vars.cmake)
include(cmake/external_libs.cmake)
include(cmake/testing.cmake)

add_subdirectory(tools)
add_subdirectory(contrib)
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
