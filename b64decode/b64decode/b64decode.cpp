// b64decode.cpp 
// Levi Seibert
// CS 484
// Problem Set #1
// This program reads base64 input from the console, converts it to ASCII, and prints the decoded data to the console

#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

// The convertToBinary function accepts a character of ciphertext, a 6-byte array, and an integer that holds the number of bits in a "byte" (only 6 bits) as parameters.
// The function calculates the base64 decimal value of the the character input. 
// The function then performs the algorithm to convert the decimal value into binary and stores the binary value into the byte array.
void convertToBinary(char val, char byte[], unsigned int byteSize)
{
	// define constants, base64 array, and a variable to hold the decimal number
	const unsigned int INDEX = 64;
	char base64[INDEX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
					   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
					   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
					   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					   'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
					   'w', 'x', 'y', 'z', '0', '1', '2', '3',
					   '4', '5', '6', '7', '8', '9', '+', '/' };
	unsigned int dec = 0;

	// for each value in the base64 character set
	for (unsigned int a = 0; a < INDEX; a++)
	{
		// if the ciphertext character matches a base64 character
		if (val == base64[a])
		{
			// store the base64 decimal value in the dec variable
			dec = a;
		}
	}

	// for each bit in the "byte"
	for (unsigned int i = 0; i < byteSize; i++)
	{
		// define a variable to hold the correct value to calculate the binary value
		unsigned int divisor = pow(2.0, ((byteSize - i) - 1));

		// if the decimal value divided by the divsor results in a 1
		if ((dec / divisor) >= 1)
		{
			// place a 1 in the byte array and subtract the divisor from the dec variable
			byte[i] = '1';
			dec -= divisor;
		}

		// else, place a 0 in the byte array
		else
		{
			byte[i] = '0';
		}
	}

	//return to main
	return;
}

// The convertToASCII function accepts two arrays as parameters, the first of which holds the bitstream of the ciphertext and the second is empty.
// The function separates the bitstream into groups of eights bits and then calculate the ASCII character for each group of eight bits.
// Finally, it places each ASCII character in the decode array.
void convertToASCII(char bits[], char decode[])
{
	// define a constant for the byte size and a counter variable
	const unsigned int BYTESIZE = 8;
	unsigned int count = 0;

	// for each byte
	for (unsigned int a = 0; bits[a] != '\0'; a += 8)
	{
		// define a variable to hold the decimal value
		unsigned int val = 0;

		// for each bit in the byte
		for (unsigned int i = 0; i < BYTESIZE; i++)
		{
			// if the end of the bitstream is reached
			if (bits[a + i] == '\0')
			{
				// store the decoded value in the encode array, increment count, place an escape sequence character at the end of the decode array, and return to main
				decode[count] = val;
				count++;
				decode[count] = '\0';
				return;
			}

			// if the bit is a 1, add the corresponding decimal equivalent to the val variable
			if (bits[a + i] == '1')
			{
				val += pow(2.0, ((BYTESIZE - i) - 1));
			}
		}

		// place the equivalent ASCII character in the encode array and increment count
		decode[count] = val;
		count++;
	}

	// place an escape sequence on the end of the decode array and return to main
	decode[count] = '\0';
	return;
}

int main()
{
	// define constants
	const unsigned int SIZE = 1000;
	const unsigned int SMALLSIZE = 7;
	const unsigned int TINYSIZE = 6;

	// declare and define character arrays
	char ciphertext[SIZE];
	char binary[SMALLSIZE] = "000000";
	char bitStream[SIZE * TINYSIZE] = "";
	char decoded[SIZE] = "";

	// get ciphertext from standard input and store in ciphertext array
	cout << "Input ciphertext: ";
	cin.getline(ciphertext, SIZE);

	// while the end of the text is not reached, convert each character in the ciphertext array to binary and append to the bitStream array
	unsigned int i = 0;
	while (ciphertext[i] != '\0')
	{
		convertToBinary(ciphertext[i], binary, TINYSIZE);
		strcat_s(bitStream, binary);
		i++;
	}

	// convert the bitStream array to ASCII decoded plaintext
	convertToASCII(bitStream, decoded);

	// display the plaintext to standard output
	cout << endl << "Plaintext: " << decoded << endl;

	return 0;
}