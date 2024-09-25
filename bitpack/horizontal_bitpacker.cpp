#include "bitpacker.h"

using namespace std;

void BitPacker::packData(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData)
{
    uint32_t maxValue = *max_element(input, input + dataSize);
    uint32_t bitCount = log2(maxValue) + 1;

    uint32_t packedSize = (dataSize * bitCount + 31) / 32;

    packedData[0] = dataSize;
    packedData[1] = bitCount;

    uint32_t bitPosition = 0;
    for (uint32_t i = 0; i < dataSize; ++i)
    {
        uint32_t byteIndex = (bitPosition / 32) + 2;
        uint32_t bitOffset = bitPosition % 32;

        packedData[byteIndex] |= (input[i] << bitOffset);

        if (bitOffset > (32 - bitCount))
        {
            packedData[byteIndex + 1] |= (input[i] >> (32 - bitOffset));
        }

        bitPosition += bitCount;
    }
}

void BitPacker::unpackData(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData)
{
    uint32_t dataSize = packedData[0];
    uint32_t bitCount = packedData[1];

    uint32_t bitPosition = 0;
    for (uint32_t i = 0; i < dataSize; ++i)
    {
        uint32_t byteIndex = (bitPosition / 32) + 2;
        uint32_t bitOffset = bitPosition % 32;

        unpackedData[i] = (packedData[byteIndex] >> bitOffset) & ((1U << bitCount) - 1);

        if (bitOffset > (32 - bitCount))
        {
            unpackedData[i] |= (packedData[byteIndex + 1] << (32 - bitOffset)) & ((1U << bitCount) - 1);
        }

        bitPosition += bitCount;
    }
}

void printPacked(uint32_t *packedData, uint32_t packedSize)
{
    for (uint32_t i = 2; i < packedSize; ++i)
    {
        cout << bitset<32>(packedData[i]) << "\n";
    }
    cout << endl;
}

void printUnpacked(uint32_t *unpackedData, uint32_t unpackedSize)
{
    for (uint32_t i = 0; i < unpackedSize; ++i)
    {
        cout << unpackedData[i] << " ";
    }
    cout << endl;
}

void generateData(vector<uint32_t> &input, uint32_t size)
{
    for (uint32_t i = 0; i < size; ++i)
    {
        input[i] = i % 17;
    }
}