#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Converts characters to hexadecimal
string to_hex(unsigned char c) {
    ostringstream oss;
    oss << hex << setfill('0') << setw(2) << (int)c;
    return oss.str();
}


string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


void write_file(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        exit(1);
    }
    file << content;
    file.close();
}

// encrypts plaintext using repeating-key XOR with the key
string repeating_key_xor(const string& plaintext, const string& key) {
    string result;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        // XOR each character of the plaintext with the corresponding key character (repeating key)
        char encrypted_char = plaintext[i] ^ key[i % key.size()];
        // converts the encrypted character to hex and append it to the result string
        result += to_hex(encrypted_char);
    }
    return result;
}

int main() {
    string choice, plaintext, input_file, output_file;
    string key = "ICE";

    cout << "Would you like to encrypt file or text from console? (Enter f for file or t for text): ";
    cin >> choice;
    cin.ignore(); // ignore for console input buffer

    if (choice == "f") {
        cout << "Enter the input file name: ";
        cin >> input_file;
        cout << "Enter the output file name: ";
        cin >> output_file;

        
        plaintext = read_file(input_file);

        // uses repeating key xor function
        string encrypted = repeating_key_xor(plaintext, key);

        // writes the encrypted content to the file
        write_file(output_file, encrypted);

        cout << "File encryption complete. Encrypted content saved to: " << output_file << endl;
    }
    else if (choice == "t") {
        
        cout << "Enter the text to encrypt: ";
        getline(cin, plaintext);

        
        string encrypted = repeating_key_xor(plaintext, key);

        
        cout << "Encrypted text: " << encrypted << endl;
    }
    else {
        cout << "Invalid choice. Please enter 'f' for file or 't' for text." << endl;
    }

    return 0;
}