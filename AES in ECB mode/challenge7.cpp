// AES in ECB mode

// using code "YELLOW SUBMARINE" exactly 16 bytes

// Use OpenSSL::Cipher give it AES-128-ECB as cipher

#include <iostream>
#include <string>
#include <fstream>
// #include <openssl/aes.h> //openssl throwing a fit for mac, looking into crypto++ git repo instead
// okay, look's like we're using cryptopp instead
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/base64.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>

using namespace std;
using namespace CryptoPP; // found the issue

/*
okay, need to:
    1. read / decode the file DONE
    2. Set up AES decryption DONE
        a. give it the key and ECB mode key is handled in main function
    3. decrypt the data DONE
    4. output to file DONE
    5. profit $$$


*/

int test_if_output_works()
{

    ifstream inputFile("encrypted.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error: couldn't open" << endl;
        return 1;
    }
    ofstream outputFile("outputFile.txt");
    if (!outputFile.is_open())
    {
        cerr << "Erro: couldn't open output file" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        outputFile << line << endl;
    }
    inputFile.close();
    outputFile.close();

    cout << "contents written to output file" << endl;

    return 0;
}

// transferring the file into da string

string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Dude, you're a senior and can't open a file?" << endl;
        return "";
    }
    string content;
    string line;
    while (getline(file, line))
    {
        content += line + "\n";
    }
    return content;
}

string decode64(const string &encoded)
{
    string decoded;
    try
    {
        StringSource ss(encoded, true, new Base64Decoder(new StringSink(decoded)));
    }
    catch (const Exception &e)
    {
        cerr << "Error during base64 decoding" << e.what() << endl;
    }
    return decoded;
}

// settting up AES decyrption now...

string decryptAES(const string &encryptedBytes, const CryptoPP::byte key[AES::DEFAULT_KEYLENGTH]) // tired of people on stackoverflow calling me stupid
{
    string decryptedBytes;
    try
    {
        ECB_Mode<AES>::Decryption decryptor;
        decryptor.SetKey(key, AES::DEFAULT_KEYLENGTH);
        StringSource ss(encryptedBytes, true, new StreamTransformationFilter(decryptor, new StringSink(decryptedBytes)));
    }
    catch (const Exception &e)
    {
        cerr << "Error during AES decryption: " << e.what() << endl;
    }

    return decryptedBytes;
}

// forgot, need to write the data to the file so we can actually see and use it

void writeToDaFile(const string &filename, const string &content)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Can't open the file, doofus" << endl;
        return;
    }
    file << content;
    cout << "Successfully written to the file: " << filename << endl;
}

// Throwing this mess into main and hoping this mac doesn't explode

#ifndef UNIT_TEST
int main()
{
    string encryptedBase64 = readFile("encrypted.txt");
    if (encryptedBase64.empty())
    {
        cerr << "Failed to read the file" << endl;
        return 1;
    }
    cout << "Read file content: " << encryptedBase64.substr(0, 100) << "..." << endl;

    // decoding base64 now...
    string encryptedBytes = decode64(encryptedBase64);
    if (encryptedBytes.empty())
    {
        cerr << "failed to decode base64 content." << endl;
        return 1;
    }
    cout << "Decoded base64 content: " << encryptedBytes.substr(0, 100) << "..." << endl;

    // AES decryption now...

    CryptoPP::byte key[AES::DEFAULT_KEYLENGTH] =
        {
            'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};

    // decrypting the file now
    string decryptedBytes = decryptAES(encryptedBytes, key);
    if (decryptedBytes.empty())
    {
        cerr << "Failed to decrypt the content." << endl;
        return 1;
    }
    cout << "Decrypted content: " << decryptedBytes.substr(0, 100) << "..." << endl;

    // write this ***** to the file
    writeToDaFile("outputFile.txt", decryptedBytes);
    cout << "Written to the file!!!" << endl;

    return 0;
}
#endif

// ohhhhhh my god I spent 2 hours debugging not realizing I had it creating a seperate file to dump the info to, not the outputfile
