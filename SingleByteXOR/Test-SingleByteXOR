// CSC414 - Cryptopals Challenge - Group 6
// Challenge 3 - Single Byte XOR Cipher Test
// Donald Reed

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <stdexcept>
#include "mysinglebytexor.h" // SingleByteXOR.cpp needs to be included for the test to work

using namespace std;

// Test for Hamming Distance to validate correct distance between strings
TEST(CryptoChallengeTests, HammingDistance) {
    string str1 = "this is a test";
    string str2 = "wokka wokka!!!";

    // expecting the hamming distance to match the known value
    EXPECT_EQ(hamming_distance(str1, str2), 37);

    // check for appropriate handling of  strings with unequal lengths
    string unequal_size_str = "short";
    EXPECT_THROW(hamming_distance(unequal_size_str, str2), invalid_argument);
}

// Test for Base64 Decoding
TEST(CryptoChallengeTests, Base64Decoding) {
    string encoded = "RG9uYWxkIGlzIHRoZSBiZXN0ZXN0";  // encoded string obtained at www.base64encode.org
    string expected = "Donald is the bestest";

    EXPECT_EQ(decodeBase64(encoded), expected);
}

// Test for English Scoring
TEST(CryptoChallengeTests, EnglishScore) {
    string valid_text = "The quick brown fox jumps over the lazy dog";
    string invalid_text = "0123456789!@#$%^&*()_+=-";

    EXPECT_GT(english_score(valid_text), english_score(invalid_text));
}

// Test for Single-Byte XOR
TEST(CryptoChallengeTests, SingleByteXOR) {
    string data = "The quick brown fox";
    char key = 0x5A; // Example key
    string result = single_byte_xor(data, key);
    string expected = single_byte_xor(result, key); // Re-encode to validate original text
    EXPECT_EQ(data, expected);
}

// Test for Key Size Edit Distance
TEST(CryptoChallengeTests, KeySizeEditDistance) {
    string data = "this is a test this is only a test"; // Sample data
    int keysize = 4; // Example keysize
    double distance = keysize_edit_distance(data, keysize);

    EXPECT_GT(distance, 0.0); // Ensure it's calculated and normalized
    EXPECT_LT(distance, 8.0); // Hamming distance per byte should be within reasonable bounds
}

// Integration Test for Full Cipher Decryption
TEST(CryptoChallengeTests, FullCipherDecryption) {
    string key = "ICE";
    string ciphertext = "Do or do not\n"
                        "There is no try";
    string encrypted = repeating_xor(ciphertext, key);
    string decrypted = repeating_xor(encrypted, key);

    EXPECT_EQ(decrypted, ciphertext);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
