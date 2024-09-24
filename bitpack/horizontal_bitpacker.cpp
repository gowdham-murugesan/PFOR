#include "bitpacker.h"

using namespace std;

vector<uint32_t> BitPacker::packData(const vector<uint32_t> &input) {
    uint32_t dataSize = input.size();
    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    uint32_t packedSize = (dataSize * bitCount + 31) / 32;

    vector<uint32_t> packedData(packedSize + 2, 0);
    packedData[0] = dataSize;
    packedData[1] = bitCount;

    uint32_t bitPosition = 0;
    for (uint32_t i = 0; i < dataSize; ++i) {
        uint32_t byteIndex = (bitPosition / 32) + 2;
        uint32_t bitOffset = bitPosition % 32;

        packedData[byteIndex] |= (input[i] << bitOffset);

        if (bitOffset > (32 - bitCount)) {
            packedData[byteIndex + 1] |= (input[i] >> (32 - bitOffset));
        }

        bitPosition += bitCount;
    }

    return packedData;
}

vector<uint32_t> BitPacker::unpackData(const vector<uint32_t> &packedData) {
    uint32_t dataSize = packedData[0];
    uint32_t bitCount = packedData[1];
    vector<uint32_t> unpackedData(dataSize, 0);

    uint32_t bitPosition = 0;
    for (uint32_t i = 0; i < dataSize; ++i) {
        uint32_t byteIndex = (bitPosition / 32) + 2;
        uint32_t bitOffset = bitPosition % 32;

        unpackedData[i] = (packedData[byteIndex] >> bitOffset) & ((1U << bitCount) - 1);

        if (bitOffset > (32 - bitCount)) {
            unpackedData[i] |= (packedData[byteIndex + 1] << (32 - bitOffset)) & ((1U << bitCount) - 1);
        }

        bitPosition += bitCount;
    }

    return unpackedData;
}

void printPacked(const vector<uint32_t> &packedData) {
    for (uint32_t i = 2; i < packedData.size(); ++i) {
        cout << bitset<32>(packedData[i]) << "\n";
    }
    cout << endl;
}

void printUnpacked(const vector<uint32_t> &unpackedData) {
    for (uint32_t i = 0; i < unpackedData.size(); ++i) {
        cout << unpackedData[i] << " ";
    }
    cout << endl;
}

void generateData(vector<uint32_t> &input, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        input[i] = i%17;
    }
}