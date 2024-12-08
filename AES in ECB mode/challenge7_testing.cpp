#include <gtest/gtest.h>
#include "challenge7.cpp"

// doing the readFile test first
TEST(ReadFileTest, HandlesIfFileIsNotFound)
{
    string content = readFile("YoThisFileDoesntExist.txt");
    EXPECT_EQ(content, "");
}

TEST(ReadFileTest, HandlesIfFileIsFound)
{
    string content = readFile("encrypted.txt");
    EXPECT_TRUE(content.size() > 0);
}

// now the decode64 testing
TEST(Decode64Test, HandlesValidBase64Decoding)
{
    string encoded = "SGVsbG8gV29ybGQ="; // should be hello world
    string decoded = decode64(encoded);
    EXPECT_EQ(decoded, "Hello World");
}

TEST(Decode64Test, HandlesInvalidBase64Decoding)
{
    string encoded = "The numbers mason....What do they mean??";
    string decoded = decode64(encoded);
    EXPECT_EQ(decoded, "");
}

// hello, decryptAES testing...
TEST(DecryptAESTest, HandlesValidAESDecryption)
{
    string encrypted = "U2FsdGVkX1+rG9JZLT35MDgonrNX9NeyiAra8wcPkag=";
    CryptoPP::byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] =
        {
            'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
    string decrypted = decryptAES(encrypted, key);
    EXPECT_EQ(decrypted, "Hello World");
}

TEST(DecryptAESTest, HandlesInvalidAESDecryption)
{
    string encrypted = "jdkaleieqjjsaj4l50akl";
    CryptoPP::byte key[AES::DEFAULT_KEYLENGTH] =
        {
            'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
    string decrypted = decryptAES(encrypted, key);
    EXPECT_EQ(decrypted, "");
}

// and finally, the writeToDaFile testing

TEST(WriteToDaFileTest, HandlesFileWrite)
{
    string content = "Hello World";
    writeToDaFile("outputFile.txt", content);
    string readContent = readFile("outputFile.txt");
    EXPECT_EQ(readContent, content + "\n");
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}