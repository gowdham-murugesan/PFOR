cmake_minimum_required(VERSION 3.22.1)

project(PFOR)

set(CMAKE_BUILD_TYPE Release)

find_package(benchmark REQUIRED)
find_package(GTest CONFIG REQUIRED)

enable_testing()

add_library(Compressor ./compress.cpp ./decompress.cpp)
add_library(Packer ./packing.cpp ./unpacking.cpp)

add_executable(main ./main.cpp)
add_executable(benchmark ./benchmark.cpp)
add_executable(compress_test ./test.cpp)

target_link_libraries(main Compressor Packer)
target_link_libraries(benchmark Compressor Packer benchmark::benchmark)
target_link_libraries(compress_test Compressor Packer GTest::gtest GTest::gtest_main)

add_test(NAME CompressorTests COMMAND compress_test)