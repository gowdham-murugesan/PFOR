#include <gtest/gtest.h>
#include "Compressor.h"

class CompressorTest : public ::testing::Test {
protected:
    void SetUp() override {
        data = {52, 51, 53, 450, 500, 57, 91, 54};
        bitWidth = 5;
        compressor = new Compressor(bitWidth);
    }

    void TearDown() override {
        delete compressor;
    }

    vector<uint32_t> data;
    int bitWidth;
    Compressor* compressor;
};

TEST_F(CompressorTest, CompressTest) {
    vector<uint32_t> compressedData = compressor->compress(data);

    EXPECT_LT(compressedData.size(), data.size());
}

TEST_F(CompressorTest, DecompressTest) {
    vector<uint32_t> compressedData = compressor->compress(data);
    vector<uint32_t> decompressedData = compressor->decompress(compressedData);

    EXPECT_EQ(decompressedData, data);
}

TEST_F(CompressorTest, LargeDataTest) {
    vector<uint32_t> largeData(1000, 52);
    vector<uint32_t> compressedData = compressor->compress(largeData);
    vector<uint32_t> decompressedData = compressor->decompress(compressedData);

    EXPECT_EQ(decompressedData, largeData);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}