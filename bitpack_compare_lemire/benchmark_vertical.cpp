#include <benchmark/benchmark.h>
#include "headers/usimdbitpacking.h"
#include "headers/bitpackingaligned.h"
#include <algorithm>

using namespace FastPForLib;

std::vector<uint32_t> generateArray(size_t N)
{
    std::vector<uint32_t> ans(N);
    for (uint32_t i = 0; i < N; ++i)
        ans[i] = i % 17;
    return ans;
}

size_t N = 16000;
std::vector<uint32_t> data = generateArray(N);

void simdpack(const std::vector<uint32_t> &data, std::vector<uint32_t> &out, const uint32_t bit)
{
    const size_t N = data.size();
    for (size_t k = 0; k < N / 128; ++k)
    {
        usimdpack(&data[0] + 128 * k, reinterpret_cast<__m128i *>(&out[0] + 4 * bit * k), bit);
    }
}

void simdunpack(const std::vector<uint32_t> &data, std::vector<uint32_t> &out, const uint32_t bit)
{
    const size_t N = out.size();
    for (size_t k = 0; k < N / 128; ++k)
    {
        usimdunpack(reinterpret_cast<const __m128i *>(&data[0] + 4 * bit * k), &out[0] + 128 * k, bit);
    }
}

void fastpack(const std::vector<uint32_t> &data, std::vector<uint32_t> &out, const uint32_t bit)
{
    const size_t N = data.size();
    for (size_t k = 0; k < N / 32; ++k)
    {
        fastpackwithoutmask_32(&data[0] + 32 * k, &out[0] + bit * k, bit);
    }
}

void fastunpack(const std::vector<uint32_t> &data, std::vector<uint32_t> &out, const uint32_t bit)
{
    const size_t N = out.size();
    for (size_t k = 0; k < N / 32; ++k)
    {
        fastunpack_32(&data[0] + bit * k, &out[0] + 32 * k, bit);
    }
}

void packVertical(const uint32_t *__restrict__ input, uint32_t *__restrict__ packedData, const uint32_t bit)
{
    uint32_t packPerInt = 32 / bit;

    uint32_t k = 0;
    for (uint32_t i = 0; i < packPerInt; i++)
    {
        uint32_t shiftAmount = bit * i;
        uint32_t blockEnd = std::min(N, ((N + (packPerInt - 1)) / packPerInt) * (i + 1));

        for (uint32_t j = 0; k < blockEnd; j++)
        {
            packedData[j] |= (input[k++] << shiftAmount);
        }
    }
}

void unpackVertical(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData, const uint32_t bit)
{
    uint32_t packPerInt = 32 / bit;
    uint32_t bitMask = (1U << bit) - 1;

    uint32_t k = 0;
    for (uint32_t i = 0; i < packPerInt; i++)
    {
        uint32_t shiftAmount = bit * i;
        uint32_t blockEnd = std::min(N, ((N + (packPerInt - 1)) / packPerInt) * (i + 1));

        for (uint32_t j = 0; k < blockEnd; j++)
        {
            unpackedData[k++] = (packedData[j] >> shiftAmount) & bitMask;
        }
    }
}

static void lemire_bitpack_simd(benchmark::State &state)
{
    std::vector<uint32_t> compressed(N + 1024);
    std::vector<uint32_t> recovered(N);
    uint32_t maxValue = *std::max_element(data.data(), data.data() + N);
    uint32_t bit = log2(maxValue) + 1;

    for (auto _ : state)
    {
        simdpack(data, compressed, bit);
        simdunpack(compressed, recovered, bit);
    }

    if (recovered != data)
        throw std::runtime_error("bug!");
}

static void lemire_bitpack(benchmark::State &state)
{
    std::vector<uint32_t> compressed(N + 1024);
    std::vector<uint32_t> recovered(N);
    uint32_t maxValue = *std::max_element(data.data(), data.data() + N);
    uint32_t bit = log2(maxValue) + 1;

    for (auto _ : state)
    {
        fastpack(data, compressed, bit);
        fastunpack(compressed, recovered, bit);
    }

    if (recovered != data)
        throw std::runtime_error("bug!");
}

static void gowdham_bitpack(benchmark::State &state)
{
    uint32_t maxValue = *std::max_element(data.data(), data.data() + N);
    uint32_t bit = log2(maxValue) + 1;

    uint32_t packPerInt = 32 / bit;
    uint32_t packedSize = (N + (packPerInt - 1)) / packPerInt + 2;

    uint32_t *compressed = new uint32_t[packedSize]{0};
    uint32_t *recovered = new uint32_t[N]{0};

    for (auto _ : state)
    {
        packVertical(data.data(), compressed, bit);
        unpackVertical(compressed, recovered, bit);
    }

    if (!std::equal(recovered, recovered + N, data.begin()))
        throw std::runtime_error("bug!");
}

BENCHMARK(lemire_bitpack_simd);
BENCHMARK(lemire_bitpack);
BENCHMARK(gowdham_bitpack);

BENCHMARK_MAIN();