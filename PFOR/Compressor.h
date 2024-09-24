#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

class Packer;

class Compressor {
public:
    Compressor(int bitwidth);
    
    vector<uint32_t> compress(const vector<uint32_t> &data);
    vector<uint32_t> decompress(const vector<uint32_t> &compressedData);

private:
    int bitwidth;
    int base;
    int numExceptions;
    vector<uint32_t> exceptions;
    int firstException;
    Packer* packer;
};

#endif