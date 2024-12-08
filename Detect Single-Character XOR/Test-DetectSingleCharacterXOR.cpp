#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "pch.h"
#include "mydetectsinglecharacterxor.h"

using namespace std;

//// Function to convert hex string into 8-bit binary
//void hexToBinary(const string& hex, unsigned char bytes[]) {
//    for (size_t i = 0; i < hex.length(); i += 2) {
//        bytes[i / 2] = static_cast<unsigned char>(strtol(hex.substr(i, 2).c_str(), nullptr, 16));
//    }
//}

// Function to decrypt XOR cipher
string decryptSingleByteXOR(const unsigned char* cipherBinary, size_t size, int key) {
    string decrypted;
    for (size_t i = 0; i < size; ++i) {
        decrypted += static_cast<char>(cipherBinary[i] ^ key);
    }
    return decrypted;
}

// Test the hexToBinary function
TEST(CryptoChallengeTests, HexToBinary) {
    string hex = "1b37373331363f78"; // Sample hex string
    unsigned char expected[] = { 0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78 };
    unsigned char actual[8];

    hexToBinary(hex, actual);

    for (size_t i = 0; i < sizeof(expected); ++i) {
        EXPECT_EQ(actual[i], expected[i]) << "Mismatch at byte " << i;
    }
}

// Test decryption logic
TEST(CryptoChallengeTests, DecryptSingleByteXOR) {
    // Sample binary data encrypted with a single-byte XOR key
    unsigned char cipherBinary[] = { 0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78 };
    size_t size = sizeof(cipherBinary);
    int key = 0x5A; // Known XOR key
    string expected = "plaintext"; // Example expected plaintext

    // Encrypt the plaintext to recreate the cipher
    string recreatedCipher;
    for (char ch : expected) {
        recreatedCipher += static_cast<char>(ch ^ key);
    }

    // Test the decryption
    string decrypted = decryptSingleByteXOR(reinterpret_cast<const unsigned char*>(recreatedCipher.c_str()), size, key);
    EXPECT_EQ(decrypted, expected);
}

// Integration test for the full decryption process
TEST(CryptoChallengeTests, FullDecryptionProcess) {
    string hexCipher = "1b37373331363f78"; // Sample XOR-encrypted hex data
    unsigned char cipherBinary[8];
    hexToBinary(hexCipher, cipherBinary);

    // Known XOR key for testing
    int key = 0x5A;
    string expected = "plaintext"; // Expected plaintext

    // Decrypt the binary data
    string decrypted = decryptSingleByteXOR(cipherBinary, sizeof(cipherBinary), key);

    EXPECT_EQ(decrypted, expected);
}

