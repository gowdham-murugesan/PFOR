#include "Compressor.h"
#include "Packer.h"

Compressor::Compressor(int bitwidth) : bitwidth(bitwidth), base(0), numExceptions(0), packer(new Packer()) {}

vector<uint32_t> Compressor::compress(const vector<uint32_t> &data)
{
    base = *min_element(data.begin(), data.end());
    int maxEncodedValue = (1 << bitwidth) - 1;

    vector<uint32_t> encodedValues(data.size());
    exceptions.clear();

    int miss[data.size()], j = 0;
    
    for (int i = 0; i < data.size(); i++)
    {
        miss[j] = i;
        j += (data[i] - base > maxEncodedValue);
        encodedValues[i] = data[i] - base;
    }

    exceptions.push_back(data[miss[0]]);
    firstException = miss[0];
    int prev = firstException;
    for (size_t i = 1; i < j; i++)
    {
        int cur = miss[i];
        exceptions[i] = data[cur];
        encodedValues[prev] = (cur - prev) - 1;
        prev = cur;
    }

    return packer->pack(encodedValues, bitwidth);
}