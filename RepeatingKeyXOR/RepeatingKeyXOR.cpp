// CSC414 - Cryptopals Challenge - Group 6
// Challenge 6 - Repeating Key XOR
// Donald Reed

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

// Calculate the hamming distance between two inputs
int hammingDistance(const vector<unsigned char>& array1, const vector<unsigned char>& array2) {
    if (array1.size() != array2.size()) {
        return -1; // Return -1 if the inputs ain't the same length
    }

    int distance = 0;

    // Loop through each byte and XOR to find differing bits
    for (size_t i = 0; i < array1.size(); i++) {
        unsigned char xorResult = array1[i] ^ array2[i];

        // Count the number of 1s in the XOR result (differing bits)
        while (xorResult) {
            distance += xorResult & 1;  // add 1 for each differing bit
            xorResult >>= 1;            // shift bits to process the next
        }
    }
    return distance;
}

// Convert base64 to into raw bytes
vector<unsigned char> base64ToBinary(const string& base64) {
    const string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    vector<unsigned char> binary; 	// output the vector of decoded bytes
    int value = 0;
    int valueb = -8;				// keep trak of how many bits are ready to be pushed out

    for (char c : base64) {
        if (c == '=') break;		// stop processing a padding character
        size_t pos = base64Chars.find(c);
        if (pos == string::npos) continue;		// skip invalid characters

        value = (static_cast<unsigned long long>(value) << 6) + pos;  // add 6 bits frofm base64 character
		
        valueb += 6;				// keep track of the number of available bits
        if (valueb >= 0) {
            binary.push_back((value >> valueb) & 0xFF); // push 8 bits out
            valueb -= 8;                              	// reduce available bits
        }
    }
    return binary;
}

// find the most likely key size
int findKeySize(const vector<unsigned char>& data, int min_size = 2, int max_size = 40) {
    double bestScore = INFINITY;
    int bestKeySize = 0;

    cout << "Key size debugging output:" << endl; // Debug header

    for (int keysize = min_size; keysize <= max_size; keysize++) {
        
        if (data.size() < keysize * 4) continue; // Ensure enough data for comparison

        double totalScore = 0;
        int comparisons = 0;

        // compare consecutive blocks of length keysize
        for (size_t i = 0; i + 2 * keysize < data.size(); i += keysize) {
            vector<unsigned char> block1(data.begin() + i, data.begin() + i + keysize);
            vector<unsigned char> block2(data.begin() + i + keysize, data.begin() + i + 2 * keysize);

            double distance = hammingDistance(block1, block2);  //get normalized distance
            totalScore += distance / keysize;
            comparisons++;
        }

        if (comparisons == 0) continue; // Avoid division by zero (no bueno)
        double averageScore = totalScore / comparisons;

        // Debug output for each key size
        cout << "Key size: " << keysize << ", Average Score: " << averageScore << endl;

        // update the best key size if the score improves
        if (averageScore < bestScore) {
            bestScore = averageScore;
            bestKeySize = keysize;
        }
    }

    return bestKeySize;
}

// find english text based on common letters and printable characters
double findEnglishWords(const string& text) {
    const string commonChars = "ETAOIN SHRDLU";  // the most common English letters (from Wheel of Fortune!)
    double score = 0;

    for (char c : text) {
        c = toupper(c);
        if (commonChars.find(c) != string::npos) {
            score++; // Reward common characters
        }
        // Penalize non-printable and control characters
        if (!isprint(static_cast<unsigned char>(c)) && c != '\n') {
            score -= 2;
        }
    }

    // Explicitly penalize strings with too many '\n'
    if (score < 0) { score = 0; } // eliminate negative scores
    return score;
}


// Break single-byte XOR
char findSingleByteKey(const vector<unsigned char>& data) {
    char bestKey = 0;
    double bestScore = 0;

    for (int key = 0; key < 256; key++) {
        if (key == 10) { continue; }	// skip over if the key is a line return
        string decoded;
        for (unsigned char byte : data) {
            decoded += byte ^ key;
        }

        double score = findEnglishWords(decoded);
        if (score > bestScore) {
            bestScore = score;
            bestKey = key;
        }
        if (key == 10 ) {
            cout << "Key: " << key << ", Decoded: " << decoded << ", Score: " << score << endl;
        }

    }

    return bestKey;
}

// Break Vigenere cipher
string breakVigenere(const vector<unsigned char>& ciphertext) {
    int keysize = findKeySize(ciphertext);
    cout << "Detected key size: " << keysize << endl;

    // Split the ciphertext into keysize blocks
    vector<vector<unsigned char>> blocks(keysize);
    for (size_t i = 0; i < ciphertext.size(); i++) {
        blocks[i % keysize].push_back(ciphertext[i]);
    }

    // Detect the key by analyzing each block
    string key;
    for (const auto& block : blocks) {
        key += findSingleByteKey(block);
    }
    cout << "Detected key: " << key << endl;

    // Decrypt the ciphertext using the key
    string decryptedText;
    for (size_t i = 0; i < ciphertext.size(); i++) {
        decryptedText += ciphertext[i] ^ key[i % keysize];
    }

    return decryptedText;
}

int main() {
    // Test Hamming distance
    string string1 = "this is a test";
    string string2 = "wokka wokka!!!";
    cout << "Hamming distance test: " << hammingDistance(
        vector<unsigned char>(string1.begin(), string1.end()),
        vector<unsigned char>(string2.begin(), string2.end())) << endl;

    // Read the base64-encoded ciphertext
    ifstream file("C:/Users/Donal/Documents/USM/CSC414/CryptoChallenge/CryptoChallenge6-Base64.txt");
    string base64_data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Decode the base64-encoded ciphertext
    vector<unsigned char> ciphertext = base64ToBinary(base64_data);

    // Break the Vigenère cipher
    string decryptedText = breakVigenere(ciphertext);
    cout << "Decrypted message:\n" << decryptedText << endl;

    return 0;
}
