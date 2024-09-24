#include "Compressor.h"
#include "Packer.h"

vector<uint32_t> Compressor::decompress(const vector<uint32_t> &compressedData)
{
    vector<uint32_t> unpackedData = packer->unpack(compressedData, bitwidth);
    vector<uint32_t> decompressed(unpackedData.size());

    int next, cur = firstException;

    for (size_t i = 0; i < decompressed.size(); i++)
    {
        decompressed[i] = base + unpackedData[i];
    }

    for (size_t i = 0; cur < decompressed.size(); i++, cur = next)
    {
        next = cur + unpackedData[cur] + 1;
        decompressed[cur] = exceptions[i];
    }

    return decompressed;
}