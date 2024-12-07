#include <"FixedXOR.h">
#include <gtest/gtest.h>

namespace {


TEST(FixedXORTest, XORTest) {
	// Ensures the result is what it should be
	string expectedOutput = "746865206b696420646f6e277420706c6179";

	string actualOutput = FixedXOR();

	cout << "Expected Output: " << expectedOutput;
	cout << "\nActual Output: " << actualOutput;
}

}
