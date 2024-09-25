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

    void packData(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData);
    void unpackData(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData);
};

class VerticalPacker : public BitPacker
{
public:
    VerticalPacker() = default;
    ~VerticalPacker() = default;
    
    void packData(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData);
    void unpackData(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData);
};

class VerticalPacker128
{
public:
    VerticalPacker128() = default;
    ~VerticalPacker128() = default;
    
    void packData(const uint32_t *__restrict__ input, uint32_t dataSize, uint32_t *__restrict__ packedData);
    void unpackData(const uint32_t *__restrict__ packedData, uint32_t *__restrict__ unpackedData);
};

void printPacked(uint32_t *packedData, uint32_t packedSize);
void printUnpacked(uint32_t *unpackedData, uint32_t unpackedSize);
void generateData(vector<uint32_t> &input, uint32_t size);

#endif