#include <iostream>
#include <bitset>
#include "Compressor.h"
#include "Packer.h"

int main() {
    vector<uint32_t> data = {52, 51, 53, 450, 500, 57, 91, 54};
    int bitWidth = 5;

    Compressor compressor(bitWidth);
    
    cout << "Before compression: ";
    for (uint32_t val : data) {
        cout << val << " ";
    }
    cout << endl;

    vector<uint32_t> compressedData = compressor.compress(data);

    cout << "Packed data: ";
    for (uint32_t val : compressedData) {
        cout << bitset<32>(val) << " ";
    }
    cout << endl;

    vector<uint32_t> decompressedData = compressor.decompress(compressedData);

    cout << "After decompression: ";
    for (uint32_t val : decompressedData) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}