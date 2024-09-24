#include "bitpacker.h"
#include <benchmark/benchmark.h>

static void HorizontalBitPacking(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);

    vector<uint32_t> packedData, unpackedData;

    BitPacker bitPacker;

    for (auto _ : state)
    {
        packedData = bitPacker.packData(input);
        unpackedData = bitPacker.unpackData(packedData);
    }
    if (input != unpackedData)
        throw std::runtime_error("Bug in horizontal!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

static void VerticalBitPacking(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);

    vector<uint32_t> packedVertical, unpackedVertical;

    VerticalPacker verticalPacker;

    for (auto _ : state)
    {
        packedVertical = verticalPacker.packVertical(input);
        unpackedVertical = verticalPacker.unpackVertical(packedVertical);
    }
    if (input != unpackedVertical)
        throw std::runtime_error("Bug in vertical!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

static void VerticalBitPacking128(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);

    vector<uint32_t> packedVertical128, unpackedVertical128;

    VerticalPacker128 verticalPacker128;

    for (auto _ : state)
    {
        packedVertical128 = verticalPacker128.packVertical128(input);
        unpackedVertical128 = verticalPacker128.unpackVertical128(packedVertical128);
    }
    if (input != unpackedVertical128)
        throw std::runtime_error("Bug in vertical!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

BENCHMARK(HorizontalBitPacking);
BENCHMARK(VerticalBitPacking);
BENCHMARK(VerticalBitPacking128);

BENCHMARK_MAIN();