//*
//
// Name: Sean Oreta
// CWID: 886349166
//

#include <iostream>
#include <fstream>
#include "cipher.cpp"

using namespace std;

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

	string decrypted = c.decrypt();
	cout << "Your decrypted message is: " << decrypted << endl;

	if (encrypted == decrypted) {
                cout << "Success!" << endl;
        }

	file.close();
        return 0;
}
