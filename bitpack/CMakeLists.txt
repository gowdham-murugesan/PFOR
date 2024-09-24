cmake_minimum_required(VERSION 3.22.1)

project(bitpack)

set(CMAKE_BUILD_TYPE Debug)

find_package(benchmark REQUIRED)
add_compile_options(-O3 -march=native -fopt-info-vec)

add_library(bitpacker ./horizontal_bitpacker.cpp ./vertical_bitpacker.cpp ./vertical_128.cpp)
add_executable(main ./main.cpp)
add_executable(benchmark ./benchmark.cpp)

target_link_libraries(main bitpacker)
target_link_libraries(benchmark bitpacker benchmark::benchmark)