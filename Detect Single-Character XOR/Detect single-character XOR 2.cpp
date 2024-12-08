// CSC414 - Cryptopals Challenge - Group 6
// Challenge 4 - Detect Single Character XOR Cipher
// Donald Reed

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Function to convert hex string into 8-bit binary
void hexToBinary(const string& hex, unsigned char bytes[]) {
    for (size_t i = 0; i < hex.length(); i += 2) {
        bytes[i / 2] = static_cast<unsigned char>(strtol(hex.substr(i, 2).c_str(), nullptr, 16));
    }
}

int main() {
    // Single-byte XOR cipher hex encoded string
    //string cipherStringHex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

 
    // Open the input file
    ifstream challengeFile4(""C:/Users/Donal/Documents/USM/CSC414/CryptoChallenge/CryptoChallenge6-Base64.txt"");
    if (!challengeFile4.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    // Open the output file
    ofstream outputFile("C:/Users/Donal/Downloads/USM/CSC414 - Intro to SE/Crypto Challenge/DecryptedChallenge4.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    // Read the entire file into a string
    string cipherStringHex((istreambuf_iterator<char>(challengeFile4)), istreambuf_iterator<char>());

    // Get the length of the cipher
    size_t cipherStringSize = cipherStringHex.length() / 2;

    // Array to store binary data
    unsigned char cipherBinary[10240];  // Assuming cipherHex is 20480 chars, binary is half that size
    hexToBinary(cipherStringHex, cipherBinary);

    // Loop through all possible ASCII keys (0-255)
    for (int key = 255; key >= 0; --key) {
        // Print key and ASCII character on screen
        cout << "ASCII Key: " << key << " (" << static_cast<char>(key) << ")" << endl;

        // Write key and ASCII character to the output file
        outputFile << "Key: " << key << " (" << static_cast<char>(key) << ")" << endl;

        // Decrypt the cipher
        for (size_t i = 0; i < cipherStringSize; ++i) {
            outputFile << static_cast<char>(cipherBinary[i] ^ key);
        }

        outputFile << endl << endl;  // Add newlines after each decryption attempt
    }

    // Close the files
    challengeFile4.close();
    outputFile.close();

    cout << "Decrypted content has been written to 'DecryptedChallenge4.txt'" << endl;

    return 0;
}
