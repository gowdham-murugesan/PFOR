#include "Packer.h"

vector<uint32_t> Packer::unpack(const vector<uint32_t> &packedData, int numB) {
    vector<uint32_t> unpackedData(inputSize);
    int pos = 0;
    
    for (size_t i = 0; i < unpackedData.size(); i++) {
        int byte = pos / 32;
        int bit = pos % 32;

        unpackedData[i] = (packedData[byte] >> bit) & ((1 << numB) - 1);
        if (bit > (32 - numB)) {
            unpackedData[i] |= (packedData[byte + 1] << (32 - bit)) & ((1 << numB) - 1);
        }

        pos += numB;
    }

    return unpackedData;
}