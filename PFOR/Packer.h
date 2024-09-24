#ifndef PACKER_H
#define PACKER_H

#include <cstdint>
#include <vector>
#include <cmath>

using namespace std;

class Packer {
public:
    vector<uint32_t> pack(const vector<uint32_t> &input, int numB);
    vector<uint32_t> unpack(const vector<uint32_t> &packedData, int numB);

private:
    int inputSize;
};

#endif