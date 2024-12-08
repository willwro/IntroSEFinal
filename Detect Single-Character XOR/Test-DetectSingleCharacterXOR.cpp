#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include<gtest/gtest.h>
#include "pch.h"
#include "mydetectsinglecharacterxor.h"

using namespace std;

// Google Test for hexToBinary
TEST(CryptoChallengeTests, HexToBinary_ValidInput) {
    string hex = "1b37373331363f78"; // Sample hex string
    unsigned char expected[] = { 0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78 };
    unsigned char actual[8]; // Output buffer

    // Call the function
    hexToBinary(hex, actual);

    // Verify that the actual output matches the expected output
    EXPECT_EQ(std::memcmp(actual, expected, sizeof(expected)), 0) << "Binary data does not match expected values.";
}

TEST(CryptoChallengeTests, HexToBinary_InvalidInput) {
    string invalidHex = "1g"; // Invalid character in hex
    unsigned char actual[1]; // Output buffer

    // Test invalid input (should not crash, but behavior depends on implementation)
    EXPECT_NO_THROW({
        hexToBinary(invalidHex, actual);
        });
}

TEST(CryptoChallengeTests, HexToBinary_EmptyInput) {
    string emptyHex = ""; // Empty string
    unsigned char actual[1]; // Output buffer (should remain untouched)

    // Call the function
    hexToBinary(emptyHex, actual);

    // No output expected for an empty input
    EXPECT_TRUE(true); // Just ensuring it doesn't crash
}
