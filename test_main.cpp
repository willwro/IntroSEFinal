#include "repeating-keyXOR.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std; 

TEST(RepeatingKeyXORTest, BasicTest) {
    string plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
                            
    string key = "ICE";
    string expected_output = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

    string actual_output = repeating_key_xor(plaintext, key);

}

TEST(XOREncryptionTest, EmptyString) {
    string plaintext = "";
    string key = "ICE";
    string expected = ""; 
    EXPECT_EQ(repeating_key_xor(plaintext, key), expected);
}




