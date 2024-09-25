#include "bitpacker.h"

using namespace std;

int main()
{
    uint32_t dataSize = 128;
    vector<uint32_t> input(dataSize);

    generateData(input, dataSize);

    for (uint32_t i = 0; i < dataSize; i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;

    uint32_t maxValue = *max_element(input.begin(), input.end());
    uint32_t bitCount = log2(maxValue) + 1;

    // Horizontal
    BitPacker bitPacker;

    uint32_t packedHorizontalSize = (dataSize * bitCount + 31) / 32 + 2;
    uint32_t *packedData = new uint32_t[packedHorizontalSize]{0};
    uint32_t *unpackedData = new uint32_t[dataSize]{0};

    bitPacker.packData(input.data(), dataSize, packedData);
    printPacked(packedData, packedHorizontalSize);

    bitPacker.unpackData(packedData, unpackedData);
    printUnpacked(unpackedData, dataSize);

    if (!equal(input.begin(), input.end(), unpackedData))
        throw runtime_error("Bug in horizontal!");

    // Vertical
    VerticalPacker verticalPacker;

    uint32_t packPerInt = 32 / bitCount;
    uint32_t packedSize = (dataSize + (packPerInt - 1)) / packPerInt + 2;

    uint32_t *packedVertical = new uint32_t[packedSize]{0};
    uint32_t *unpackedVertical = new uint32_t[dataSize]{0};

    verticalPacker.packData(input.data(), dataSize, packedVertical);
    printPacked(packedVertical, packedSize);

    verticalPacker.unpackData(packedVertical, unpackedVertical);
    printUnpacked(unpackedVertical, dataSize);

    if (!equal(input.begin(), input.end(), unpackedVertical))
        throw runtime_error("Bug in vertical!");

    // Vertical 128
    VerticalPacker128 verticalPacker128;

    uint32_t blockSize = 128;
    uint32_t totalBlocks = (dataSize + blockSize - 1) / blockSize;
    uint32_t rowPerBlock = (blockSize + (packPerInt - 1)) / packPerInt;
    uint32_t packedVertical128Size = totalBlocks * rowPerBlock + 2;

    uint32_t *packedVertical128 = new uint32_t[packedVertical128Size]{0};
    uint32_t *unpackedVertical128 = new uint32_t[dataSize]{0};

    verticalPacker128.packData(input.data(), dataSize, packedVertical128);
    printPacked(packedVertical128, packedVertical128Size);

    verticalPacker128.unpackData(packedVertical128, unpackedVertical128);
    printUnpacked(unpackedVertical128, dataSize);

    if (!equal(input.begin(), input.end(), unpackedVertical128))
        throw runtime_error("Bug in vertical128!");

    delete[] packedData;
    delete[] unpackedData;
    delete[] packedVertical;
    delete[] unpackedVertical;
    delete[] packedVertical128;
    delete[] unpackedVertical128;

    return 0;
}