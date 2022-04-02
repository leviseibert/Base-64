# Base-64

This set of programs demonstrated Base-64 encoding of ASCII values.

Note: These programs do not perform encryption.  There are no keys are manipulation of the data itself.  Rather, the program simply represents the data in a new way (base64 encoding rather than ASCII encoding).  
For example, if I run the encode program with the test plaintext “Test,” I receive the encoded text (it is labelled as “Ciphertext” in the program, but it isn’t really a ciphertext) of VGVzdA.  
The binary representations of both these strings are identical (except for the extra zeros on the end of the encoded text which are added to make a complete set of six bits).
“Test” (ASCII) binary: 01010100 01100101 01110011 01110100
“VGVzdA” (base64) binary: 010101 000110 010101 110011 011101 000000
If you input the “VGVzdA” as the “Ciphertext” in the decode program, you will also receive “Test” as the output, without there being any keys involved.

b64encode.cpp accepts an ASCII string from the console, converts it to Base-64 and prints the encoded value to the console.
b64decode.cpp accepts a Base-64 string from the console, converts it to ASCII and prints the decoded value to the console.
