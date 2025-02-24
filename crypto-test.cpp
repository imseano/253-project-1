//*
//
// Name: Sean Oreta
// CWID: 886349166
//

#include <iostream>
#include <fstream>
#include "cipher.cpp"

using namespace std;

void testDecryption(Cipher& c, const string& plaintext, const string& encrypted);

int main() {
	fstream file;
	string filename;
	string input;

        cout << "Initializing Cryptography Test..." << endl << "hi" << endl;

	string message = "Please input the name of the file to be encrypted: ";
	cout << message << endl;
	cin >> filename;

	file.open(filename, ios::in);
        if (!file) {
                cout << "File not found." << endl;
                return 1;
	}

	// Write contents of file to string
	string line;
	while (getline(file, line)) {
		input += line + "\n";
        }

	cout << input << endl;
	Cipher c(input);
	c.generateCubes(input);

	string encrypted = c.encrypt();
        cout << "Your encrypted message is: " << encrypted << endl;

	testDecryption(c, input, encrypted);

	//string decrypted = c.decrypt();
	//cout << "Your decrypted message is: " << decrypted << endl;

	//if (encrypted == decrypted) {
          //      cout << "Success!" << endl;
        //}

	file.close();
        return 0;
}

// ChatGPT Function to test the decryption and compare with original plaintext
void testDecryption(Cipher& c, const std::string& plaintext, const std::string& encrypted) {
    std::string decrypted = c.decrypt();

    std::cout << "Decrypted: " << decrypted << std::endl;
    std::cout << "Original:  " << plaintext << std::endl;

    // Compare each character and point out mismatches
    bool mismatchFound = false;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        if (decrypted[i] != plaintext[i]) {
            std::cout << "Mismatch at position " << i << ": Expected '" << plaintext[i]
                      << "', but got '" << decrypted[i] << "'\n";
            mismatchFound = true;
        }
    }

    if (!mismatchFound) {
        std::cout << "Strings match!\n";
    }
}
