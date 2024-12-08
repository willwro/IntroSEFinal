// Cryptopals Challenge - Group 6
// Task: Challenge 1 - convert hex to base64
// Member: Arianne Kris M. Roessling

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>
#include <sstream>


using namespace std;


// Encoding characters of Base64
const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz"
                                 "0123456789";


// Convert hex string to raw bytes
vector<unsigned char> hex_to_bytes(const string& hex) {
    vector<unsigned char> bytes;

    for (size_t i = 0; i < hex.length(); i += 2) {
        string byte_str = hex.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(strtol(byte_str.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }

    return bytes;
}

// Base64 encoding function
string base64_encode(const vector<unsigned char>& bytes) {
    string base64;
    int val = 0, val2 = -6;
    for (unsigned char c : bytes) {
        val = (val << 8) + c;
        val2 += 8;
        while (val2 >= 0) {
            base64.push_back(base64_chars[(val >> val2) & 0x3F]);
            val2 -= 6;
        }
    }
    if (val2 > -6) base64.push_back(base64_chars[((val << 8) >> (val2 + 8)) & 0x3F]);
    while (base64.size() % 4) base64.push_back('=');
    return base64;
}


int main() {
    // Hex string input
    string hex_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    cout << "hex string: " << hex_string <<  endl;
    
    // Convert hex to raw bytes
    vector<unsigned char> bytes = hex_to_bytes(hex_string);

    // Encode raw bytes to base64
    string base64_string = base64_encode(bytes);

    // Output the result
    cout << "Base64 encoded string: " << base64_string << endl;



    return 0;
}


