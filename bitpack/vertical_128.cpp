#include "bitpacker.h"
#define BLOCK_SIZE 128

using namespace std;

void VerticalPacker128::packVertical128(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData)
{
    uint32_t maxValue = *max_element(input, input + dataSize);
    uint32_t bitCount = log2(maxValue) + 1;

    const uint32_t blockSize = BLOCK_SIZE;
    uint32_t packPerInt = 32 / bitCount;

    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;

    uint32_t rowPerBlock = (blockSize + (packPerInt - 1)) / packPerInt;

    packedData[0] = dataSize;
    packedData[1] = bitCount;

    uint32_t k = 0;
    for (uint32_t block = 0; block < totalBlocks; block++)
    {
        for (uint32_t i = 0; i < packPerInt; i++)
        {
            uint32_t shiftAmount = bitCount * i;
            uint32_t blockEnd = min((block + 1) * blockSize, (block * blockSize) + rowPerBlock * (i + 1));

            for (uint32_t j = 2 + block * rowPerBlock; k < blockEnd; j++)
            {
                packedData[j] |= (input[k++] << shiftAmount);
            }
        }
    }
}

void VerticalPacker128::unpackVertical128(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData)
{
    uint32_t dataSize = packedData[0];
    uint32_t bitCount = packedData[1];
    uint32_t packPerInt = 32 / bitCount;
    const uint32_t blockSize = BLOCK_SIZE;
    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;
    uint32_t rowPerBlock = (blockSize + (packPerInt - 1)) / packPerInt;
    uint32_t bitMask = (1U << bitCount) - 1;

    uint32_t k = 0;
    for (uint32_t block = 0; block < totalBlocks; block++)
    {
        for (uint32_t i = 0; i < packPerInt; i++)
        {
            uint32_t shiftAmount = bitCount * i;
            uint32_t blockEnd = min((block + 1) * blockSize, (block * blockSize) + rowPerBlock * (i + 1));

            for (uint32_t j = 2 + block * rowPerBlock; k < blockEnd; j++)
            {
                unpackedData[k++] = (packedData[j] >> shiftAmount) & bitMask;
            }
        }
    }
}