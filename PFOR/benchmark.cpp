#include <benchmark/benchmark.h>
#include "Compressor.h"

class CompressorBenchmark : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) override {
        data = {52, 51, 53, 450, 500, 57, 91, 54};
        bitWidth = 5;

        compressor = new Compressor(bitWidth);
        compressedData = compressor->compress(data);
    }

    void TearDown(const ::benchmark::State& state) override {
        delete compressor;
    }

    std::vector<uint32_t> data;
    int bitWidth;
    Compressor* compressor;
    std::vector<uint32_t> compressedData;
};

BENCHMARK_F(CompressorBenchmark, Compress)(benchmark::State& state) {
    for (auto _ : state) {
        compressor->compress(data);
    }
}

BENCHMARK_F(CompressorBenchmark, Decompress)(benchmark::State& state) {
    for (auto _ : state) {
        compressor->decompress(compressedData);
    }
}

BENCHMARK_MAIN();