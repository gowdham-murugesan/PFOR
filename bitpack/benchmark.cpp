#include "bitpacker.h"
#include <benchmark/benchmark.h>

static void HorizontalBitPacking(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);
    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    BitPacker bitPacker;

    uint32_t packedHorizontalSize = (dataSize * bitCount + 31) / 32 + 2;
    uint32_t *packedData = new uint32_t[packedHorizontalSize]{0};
    uint32_t *unpackedData = new uint32_t[dataSize]{0};

    for (auto _ : state)
    {
        bitPacker.packData(input.data(), dataSize, packedData);
        bitPacker.unpackData(packedData, unpackedData);
    }
    if (!equal(input.begin(), input.end(), unpackedData))
        throw runtime_error("Bug in horizontal!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

static void VerticalBitPacking(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);
    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    VerticalPacker verticalPacker;

    uint32_t packPerInt = 32 / bitCount;
    uint32_t packedSize = (dataSize + (packPerInt - 1)) / packPerInt + 2;

    uint32_t *packedVertical = new uint32_t[packedSize]{0};
    uint32_t *unpackedVertical = new uint32_t[dataSize]{0};

    for (auto _ : state)
    {
        verticalPacker.packData(input.data(), dataSize, packedVertical);
        verticalPacker.unpackData(packedVertical, unpackedVertical);
    }
    if (!equal(input.begin(), input.end(), unpackedVertical))
        throw runtime_error("Bug in vertical!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

static void VerticalBitPacking128(benchmark::State &state)
{
    uint32_t dataSize = 16000;
    vector<uint32_t> input(dataSize);
    generateData(input, dataSize);
    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    VerticalPacker128 verticalPacker128;

    uint32_t blockSize = 128;
    uint32_t packPerInt = 32 / bitCount;
    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;
    uint32_t rowPerBlock = (blockSize + (packPerInt - 1)) / packPerInt;
    uint32_t packedVertical128Size = totalBlocks * rowPerBlock + 2;

    uint32_t *packedVertical128 = new uint32_t[packedVertical128Size]{0};
    uint32_t *unpackedVertical128 = new uint32_t[dataSize]{0};

    for (auto _ : state)
    {
        verticalPacker128.packData(input.data(), dataSize, packedVertical128);
        verticalPacker128.unpackData(packedVertical128, unpackedVertical128);
    }
    if (!equal(input.begin(), input.end(), unpackedVertical128))
        throw runtime_error("Bug in vertical128!");

    state.SetItemsProcessed(state.iterations() * dataSize);
}

BENCHMARK(HorizontalBitPacking);
BENCHMARK(VerticalBitPacking);
BENCHMARK(VerticalBitPacking128);

BENCHMARK_MAIN();