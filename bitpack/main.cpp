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

    // Horizontal
    BitPacker bitPacker;

    vector<uint32_t> packedData = bitPacker.packData(input);
    printPacked(packedData);

    vector<uint32_t> unpackedData = bitPacker.unpackData(packedData);
    printUnpacked(unpackedData);

    if (input != unpackedData)
        throw std::runtime_error("Bug in horizontal!");

    // Vertical
    VerticalPacker verticalPacker;

    vector<uint32_t> packedVertical = verticalPacker.packVertical(input);
    printPacked(packedVertical);

    vector<uint32_t> unpackedVertical = verticalPacker.unpackVertical(packedVertical);
    printUnpacked(unpackedVertical);

    if (input != unpackedVertical)
        throw std::runtime_error("Bug in vertical!");

    // Vertical 128
    VerticalPacker128 verticalPacker128;

    vector<uint32_t> packedVertical128 = verticalPacker128.packVertical128(input);
    printPacked(packedVertical128);

    vector<uint32_t> unpackedVertical128 = verticalPacker128.unpackVertical128(packedVertical128);
    printUnpacked(unpackedVertical128);

    if (input != unpackedVertical128)
        throw std::runtime_error("Bug in vertical128!");

    return 0;
}