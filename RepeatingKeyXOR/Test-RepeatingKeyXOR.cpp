// CSC414 - Cryptopals Challenge - Group 6
// Google Test - Repeating Key XOR
// Donald Reed

#include <gtest/gtest.h>
#include "pch.h"
#include <vector>
#include <string>
#include "myrepeatingkeyxor.h" // Basically, just changing the file extention from .cpp to .h

using namespace std;

// Test hammingDistance function
TEST(HammingDistanceTests, BasicTest) {
    vector<unsigned char> str1{ 't', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't' };
    vector<unsigned char> str2{ 'w', 'o', 'k', 'k', 'a', ' ', 'w', 'o', 'k', 'k', 'a', '!', '!', '!' };
    EXPECT_EQ(hammingDistance(str1, str2), 37); // Expected result: 37
}

TEST(HammingDistanceTests, InvalidInput) {
    vector<unsigned char> str1{ 't', 'h', 'i', 's' };
    vector<unsigned char> str2{ 'w', 'o', 'k', 'k', 'a' };
    EXPECT_EQ(hammingDistance(str1, str2), -1); // Expected for unequal lengths
}

// Test base64ToBinary function
TEST(Base64ToBinaryTests, BasicTest) {
    string base64 = "VGhpcyBpcyBhIHRlc3Q="; // "This is a test"
    vector<unsigned char> expected{ 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'a', ' ', 't', 'e', 's', 't' };
    EXPECT_EQ(base64ToBinary(base64), expected);
}

// Test findKeySize function
TEST(FindKeySizeTests, KeySizeTest) {
    string ciphertext = "All your Base-64 belong to us";
    vector<unsigned char> data = base64ToBinary(ciphertext);
    int keysize = findKeySize(data);
    EXPECT_GT(keysize, 0); // Key size should be greater than 0
}

// Test single-byte XOR decryption
TEST(SingleByteXORTests, DecryptionTest) {
    // Created a long test string - a short one caused issues
    string original = "Hello World This Is A Test";
    vector<unsigned char> encoded;

    // Encode the string
    for (char c : original) {
        encoded.push_back(c ^ 42);
    }

    // Find that key!
    char found_key = findSingleByteKey(encoded);

    // Test the key
    EXPECT_EQ(found_key, 42);

    // Verify decoding works
    string decoded;
    for (unsigned char byte : encoded) {
        decoded += byte ^ found_key;
    }
    EXPECT_EQ(decoded, original);
}


// Test breaking the Vigenere cipher
TEST(BreakVigenereTests, FullDecryptionTest) {
    string base64 = "VGhlIHRleHQgdG8gZGVjcnlwdCBzaG91bGQgaGVyZQ=="; // Example ciphertext
    vector<unsigned char> ciphertext = base64ToBinary(base64);
    string plaintext = breakVigenere(ciphertext);
    EXPECT_FALSE(plaintext.empty()); // Plaintext should not be empty
    EXPECT_NE(plaintext.find("The text"), string::npos); // Check if part of the plaintext is present
}
