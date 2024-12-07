//Cryptopals Challenge - Group 6
//Task: Challenge 2 - Fixed XOR
//Member: Donald Roberts (DJ)

#include <iostream>
#include <string>
#include <sstream>


using namespace::std;


int main() {
	//declares the two buffers and an empty stringstream
	string xor1 = "1c0111001f010100061a024b53535009181c";
	string xor2 = "686974207468652062756c6c277320657965";
	stringstream ss;

	//outputs the two buffers
	cout << "String 1: " + xor1 << endl;
	cout << "\nString 2: " + xor2 << endl;

	int i = 0;
	//loop to XOR
	while (i != xor1.length()) {

		//takes two digits from each string
		string a = xor1.substr(i, 2);
		string b = xor2.substr(i, 2);

		//converts the hex values into decimal
		int hex1 = stoi(a, 0, 16);
		int hex2 = stoi(b, 0, 16);

		//XOR's the two integers and adds them to a string stream
		//simultaneously converts back to hex
		ss << hex << (hex1 ^ hex2);

		//increments loop
		i += 2;
	}
	//sets result as the stringstream
	string xorResult = ss.str();

	//outputs result
	cout << "\n\nXOR Result: " << xorResult << endl;
	return 0;
}
