// b64encode.cpp 
// Levi Seibert
// CS 484
// Problem Set #1
// This program reads input from the console, converts it to base64, and prints the encoded data to the console

#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;


// The convertToBinary function accepts a character of plaintext, an 8-byte array, and an integer that holds the number of bits in a byte as parameters.
// The function calculates the ASCII decimal value of the the character input. 
// The function then performs the algorithm to convert the decimal value into binary and stores the binary value into the byte array.
void convertToBinary(char val, char byte[], int byteSize)
{
	// store the ASCII value of the character in the variable dec
	unsigned int dec = val - 0;

	// for each of the bits in the byte
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

	// return to main
	return;
}

// The convertToBase64 function accepts two arrays as parameters, the first of which holds the bitstream of the plaintext and the second is empty.
// The function separates the bitstream into groups of six bits and then calculate the base64 character for each group of six bits.
// Finally, it places each base64 character in the encode array.
void convertToBase64(char bits[], char encode[])
{
	// define constants, base64 array, and a counter variable
	const unsigned int SMALLSIZE = 6;
	const unsigned int INDEX = 64;
	char base64[INDEX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
					   'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					   'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
					   'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
					   'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					   'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
					   'w', 'x', 'y', 'z', '0', '1', '2', '3',
					   '4', '5', '6', '7', '8', '9', '+', '/' };
	unsigned int count = 0;

	// for each group of six bits
	for (unsigned int a = 0; bits[a] != '\0'; a += 6)
	{
		// define a variable to hold the decimal value
		unsigned int val = 0;

		// for each of the bits in the six bit group
		for (unsigned int i = 0; i < SMALLSIZE; i++)
		{
			// if the end of the bitstream is reached
			if (bits[a + i] == '\0')
			{
				// store the encoded value in the encode array, increment count, place an escape sequence character at the end of the encode array, and return to main 
				encode[count] = base64[val];
				count++;
				encode[count] = '\0';
				return;
			}

			// if the bit is a 1, add the corresponding decimal equivalent to the val variable
			if (bits[a + i] == '1')
			{
				val += pow(2.0, ((SMALLSIZE - i) - 1));
			}
		}

		// place the equivalent base64 character in the encode array and increment count
		encode[count] = base64[val];
		count++;
	}

	// place an escape sequence on the end of the encode array and return to main
	encode[count] = '\0';
	return;
}

int main()
{
	// define constants
	const unsigned int SIZE = 1000;
	const unsigned int BIGSIZE = 9;
	const unsigned int BYTESIZE = 8;

	// declare and define character arrays
	char plaintext[SIZE];
	char binary[BIGSIZE] = "00000000";
	char bitStream[SIZE * BYTESIZE] = "";
	char encoded[SIZE] = "";

	// get plaintext from standard input and store in plaintext array
	cout << "Input plaintext: ";
	cin.getline(plaintext, SIZE);

	// while the end of the text is not reached, convert each character in the plaintext array to binary and append to the bitStream array
	unsigned int i = 0;
	while (plaintext[i] != '\0')
	{
		convertToBinary(plaintext[i], binary, BYTESIZE);
		strcat_s(bitStream, binary);
		i++;
	}

	// convert the bitStream array to base64 encoded ciphertext
	convertToBase64(bitStream, encoded);

	// display the ciphertext to standard output
	cout << endl << "Ciphertext: " << encoded << endl;

	return 0;
}