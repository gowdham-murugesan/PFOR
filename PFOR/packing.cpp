#include "Packer.h"

vector<uint32_t> Packer::pack(const vector<uint32_t> &input, int numB) {
    inputSize = input.size();
    int encodedSize = ceil(input.size() * (numB / 32.0));
    vector<uint32_t> packedData(encodedSize, 0);

    int pos = 0;
    for (size_t i = 0; i < input.size(); i++) {
        int byte = pos / 32;
        int bit = pos % 32;

        packedData[byte] |= (input[i] << bit);
        if (bit > (32 - numB)) {
            packedData[byte + 1] |= (input[i] >> (32 - bit));
        }

        pos += numB;
    }

    return packedData;
}