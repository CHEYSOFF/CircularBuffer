cmake_minimum_required(VERSION 3.24)
project(labwork_8_CHEYSOFF)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)