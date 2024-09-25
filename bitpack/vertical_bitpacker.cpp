#include "bitpacker.h"

using namespace std;

void VerticalPacker::packVertical(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData)
{
    uint32_t maxValue = *max_element(input, input + dataSize);
    uint32_t bitCount = log2(maxValue) + 1;
    uint32_t packPerInt = 32 / bitCount;

    packedData[0] = dataSize;
    packedData[1] = bitCount;

    uint32_t k = 0;
    for (uint32_t i = 0; i < packPerInt; i++)
    {
        uint32_t shiftAmount = bitCount * i;
        uint32_t blockEnd = min(dataSize, ((dataSize + (packPerInt - 1)) / packPerInt) * (i + 1));

        for (uint32_t j = 2; k < blockEnd; j++)
        {
            packedData[j] |= (input[k++] << shiftAmount);
        }
    }
}

void VerticalPacker::unpackVertical(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData)
{
    uint32_t dataSize = packedData[0];
    uint32_t bitCount = packedData[1];
    uint32_t packPerInt = 32 / bitCount;
    uint32_t bitMask = (1U << bitCount) - 1;

    uint32_t k = 0;
    for (uint32_t i = 0; i < packPerInt; i++)
    {
        uint32_t shiftAmount = bitCount * i;
        uint32_t blockEnd = min(dataSize, ((dataSize + (packPerInt - 1)) / packPerInt) * (i + 1));

        for (uint32_t j = 2; k < blockEnd; j++)
        {
            unpackedData[k++] = (packedData[j] >> shiftAmount) & bitMask;
        }
    }
}