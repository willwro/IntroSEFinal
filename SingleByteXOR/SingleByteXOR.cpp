// CSC414 - Cryptopals Challenge - Group 6
// Challenge 3 - Single Byte XOR Cipher
// Donald Reed

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include <numeric>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <curl/curl.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

using namespace std;

// Function to calculate the Hamming distance (edit distance) between two byte buffers
int hamming_distance(const string& buf1, const string& buf2) {
    if (buf1.size() != buf2.size()) {
        throw invalid_argument("Buffers must be of equal length");
    }
    int distance = 0;
    for (size_t i = 0; i < buf1.size(); ++i) {
        distance += bitset<8>(buf1[i] ^ buf2[i]).count();
    }
    return distance;
}

// Function to decode Base64 string using OpenSSL
string decodeBase64(const string& encoded) {
    BIO* bio, * b64;
    char* decoded_data = (char*)malloc(encoded.size());
    memset(decoded_data, 0, encoded.size());

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_mem_buf(encoded.c_str(), -1);
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    int decoded_length = BIO_read(bio, decoded_data, encoded.size());
    BIO_free_all(bio);

    string result(decoded_data, decoded_length);
    free(decoded_data);
    return result;
}

// Function to score English text (based on common letters and spaces)
int english_score(const string& text) {
    const string common_chars = "ETAOIN SHRDLU";
    int score = 0;
    for (char c : text) {
        if (isalpha(c) || isspace(c)) {
            if (common_chars.find(toupper(c)) != string::npos) {
                score += common_chars.find(toupper(c)) + 1;
            }
            score++;
        }
    }
    return score;
}

// Single-byte XOR function for a block
string single_byte_xor(const string& data, char key) {
    string result;
    for (char c : data) {
        result += c ^ key;
    }
    return result;
}

// Function to calculate normalized Hamming distance for a given key size
double keysize_edit_distance(const string& ciphertext, int keysize) {
    int num_blocks = ciphertext.size() / keysize;
    double total_distance = 0;
    int comparisons = 0;

    for (int i = 0; i < num_blocks - 1; ++i) {
        string block1 = ciphertext.substr(i * keysize, keysize);
        string block2 = ciphertext.substr((i + 1) * keysize, keysize);
        total_distance += hamming_distance(block1, block2) / static_cast<double>(keysize);
        ++comparisons;
    }

    return total_distance / comparisons;
}

// Repeating key XOR function for decryption
string repeating_xor(const string& data, const string& key) {
    string result;
    for (size_t i = 0; i < data.size(); ++i) {
        result += data[i] ^ key[i % key.size()];
    }
    return result;
}

// Function to fetch data from a URL (requires libcurl)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string fetch_url(const string& url) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    // Fetch and decode the Base64 encrypted text
    string url = "C:\\Users\\Donal\\Documents\\USM\\CSC414\\CryptoChallenge\\CryptoChallenge6-Base64.txt";
    string base64_encoded_data = fetch_url(url);
    string data = decodeBase64(base64_encoded_data);

    // Find the best key size
    int best_keysize = 2;
    double best_distance = keysize_edit_distance(data, best_keysize);
    for (int keysize = 2; keysize <= 40; ++keysize) {
        double distance = keysize_edit_distance(data, keysize);
        if (distance < best_distance) {
            best_distance = distance;
            best_keysize = keysize;
        }
    }

    cout << "Best key size: " << best_keysize << endl;

    // Break ciphertext into blocks and transpose based on key size
    vector<string> blocks(best_keysize);
    for (size_t i = 0; i < data.size(); ++i) {
        blocks[i % best_keysize] += data[i];
    }

    // Find the single-byte key for each block and build the repeating key
    string key;
    for (const auto& block : blocks) {
        int best_score = -1;
        char best_key = 0;
        for (int k = 0; k < 256; ++k) {
            string decrypted = single_byte_xor(block, k);
            int score = english_score(decrypted);
            if (score > best_score) {
                best_score = score;
                best_key = k;
            }
        }
        key += best_key;
    }

    cout << "Detected Key: " << key << endl;

    // Decrypt the ciphertext using the repeating key XOR
    string plaintext = repeating_xor(data, key);

    // Output the first 150 characters of the plaintext
    cout << "Decrypted Text (first 150 chars):\n" << plaintext.substr(0, 150) << endl;

    return 0;
}
