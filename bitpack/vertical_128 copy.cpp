#include "bitpacker.h"
#define BLOCK_SIZE 128

using namespace std;

vector<uint32_t> VerticalPacker128::packVertical128(const vector<uint32_t> &input)
{
    uint32_t dataSize = input.size();
    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    const uint32_t blockSize = BLOCK_SIZE;
    uint32_t packPerInt = 32 / bitCount;

    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;
    uint32_t packedSize = totalBlocks * ((blockSize + (packPerInt - 1)) / packPerInt) + 2;

    vector<uint32_t> packedData(packedSize, 0);
    packedData[0] = dataSize;
    packedData[1] = bitCount;

    uint32_t k = 0;
    for (uint32_t block = 0; block < totalBlocks; block++)
    {
        for (uint32_t i = 0; i < packPerInt; i++)
        {
            uint32_t shiftAmount = bitCount * i;
            uint32_t blockEnd = min(min(dataSize, (block + 1) * blockSize), (block * blockSize) + ((blockSize + packPerInt - 1) / packPerInt) * (i + 1));

            for (uint32_t j = 2 + block * ((blockSize + packPerInt - 1) / packPerInt); k < blockEnd; j++)
            {
                packedData[j] |= (input[k++] << shiftAmount);
            }
        }
    }

    return packedData;
}

vector<uint32_t> VerticalPacker128::unpackVertical128(const vector<uint32_t> &packedData)
{
    uint32_t dataSize = packedData[0];
    uint32_t bitCount = packedData[1];
    uint32_t packedSize = packedData.size();
    uint32_t packPerInt = 32 / bitCount;
    const uint32_t blockSize = BLOCK_SIZE;
    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;
    uint32_t bitMask = (1U << bitCount) - 1;

    vector<uint32_t> unpackedData(dataSize, 0);

    uint32_t k = 0;
    for (uint32_t block = 0; block < totalBlocks; block++)
    {
        for (uint32_t i = 0; i < packPerInt; i++)
        {
            uint32_t shiftAmount = bitCount * i;
            uint32_t blockEnd = min(min(dataSize, (block + 1) * blockSize), (block * blockSize) + ((blockSize + packPerInt - 1) / packPerInt) * (i + 1));

            for (uint32_t j = 2 + block * ((blockSize + packPerInt - 1) / packPerInt); k < blockEnd; j++)
            {
                unpackedData[k++] = (packedData[j] >> shiftAmount) & bitMask;
            }
        }
    }

    return unpackedData;
}