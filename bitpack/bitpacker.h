#ifndef BITPACKER_H
#define BITPACKER_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

class BitPacker
{
public:
    BitPacker() = default;
    ~BitPacker() = default;

    vector<uint32_t> packData(const vector<uint32_t> &input);
    vector<uint32_t> unpackData(const vector<uint32_t> &packedData);
};

class VerticalPacker
{
public:
    VerticalPacker() = default;
    ~VerticalPacker() = default;
    
    vector<uint32_t> packVertical(const vector<uint32_t> &input);
    vector<uint32_t> unpackVertical(const vector<uint32_t> &packedData);
};

class VerticalPacker128
{
public:
    VerticalPacker128() = default;
    ~VerticalPacker128() = default;
    
    vector<uint32_t> packVertical128(const vector<uint32_t> &input);
    vector<uint32_t> unpackVertical128(const vector<uint32_t> &packedData);
};

void printPacked(const vector<uint32_t> &packedData);
void printUnpacked(const vector<uint32_t> &unpackedData);
void generateData(vector<uint32_t> &input, uint32_t size);

#endif