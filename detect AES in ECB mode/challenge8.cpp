/*
cryptopals set 1 challenge 8: Detect AES in ECB mode

ECB has weakness in pattern repition, look for repeated 16-byte blocks

1. Read the file DONE

2. Convert the hex to bytes DONE

3. Detect repeatable 16-byte blocks
    function to split the byte array into 16 byte blocks
    function to see which 16 byte block is the most repeated

4. Idenitfy ECB
    should be the one with most repeated

*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

// want to store in array, has to have the line count of ciphertext.txt
void readFile(const string &filename, string ciphertext[], int maxLines, int &numLines)
{
    ifstream file(filename);
    string line;
    numLines = 0;

    // reading the file now...
    while (getline(file, line) && numLines < maxLines)
    {
        ciphertext[numLines++] = line;
    }
    file.close();
}

// okay... hex to bytes now...
void hex_to_bytes(const string &hex, uint8_t bytes[], int &byteLength)
{
    byteLength = hex.length() / 2; // each byte is 2 hex, so, logically, divide by 2 to get bytes?
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        string byteString = hex.substr(i, 2);
        bytes[i / 2] = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16)); // already giving me a headache
    }
}

// splitting into 16 bit blocks now
void splitBlocks(const uint8_t bytes[], int byteLength, uint8_t blocks[][16], int &numBlocks)
{
    numBlocks = byteLength / 16;
    for (int i = 0; i < numBlocks; ++i)
    {
        memcpy(blocks[i], &bytes[i * 16], 16); // looks like prog. langs taught me something
    }
}

// moving on to counting repated blocks
int countRepeated(const uint8_t blocks[][16], int numBlocks)
{
}

int main()
{

    const int maxLines = 205; // number of lines of ciphertext.txt
    const int maxBytes = 256; // the amount of bytes in a single line of ciphertext (hopefully)
    string filename = "ciphertext.txt";
    string ciphertext[maxLines];
    int numLines = 0;

    readFile(filename, ciphertext, maxLines, numLines);

    // printing the ciphertext to make sure it works (yeah yeah I know googleTest should be doing this)
    /* for (int i = 0; i < numLines; i++)
     {
         cout << ciphertext[i] << endl;
     }
     */
    // she reads

    for (int i = 0; i < numLines; ++i)
    {
        uint8_t bytes[maxBytes];
        int byteLength = 0;
        hex_to_bytes(ciphertext[i], bytes, byteLength); // feel like a wizard deciphering ancient scrolls trying to read stackoverflow posts from 8 years ago

        // testing again
        /* cout << "ciphertext " << i + 1 << " in bytes: "; // start this from 1, not 0
         for (int j = 0; j < byteLength; ++j)
         {
             cout << hex << static_cast<int>(bytes[j]) << " ";
         }
         cout << endl; */
        // she runs
    }

    return 0;
}