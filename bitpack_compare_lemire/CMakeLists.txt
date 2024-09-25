cmake_minimum_required(VERSION 3.22.1)

project(bitpack_compare)

set(CMAKE_BUILD_TYPE Release)

find_package(benchmark REQUIRED)
add_compile_options(-O3 -march=native)

add_executable(benchmark_vertical ./benchmark_vertical.cpp)

add_library(bitpacker ./bitpackingaligned.cpp ./simdunalignedbitpacking.cpp)

target_link_libraries(benchmark_vertical bitpacker benchmark::benchmark)