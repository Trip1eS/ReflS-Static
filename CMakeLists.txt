cmake_minimum_required(VERSION 3.13.4)
project(ReflS)

set(CMAKE_CXX_STANDARD 20)

add_library(ReflS INTERFACE)

set(REFLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(ReflS INTERFACE ${REFLS_INCLUDE_DIR})

add_subdirectory(test)