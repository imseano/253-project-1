#include "cipher.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	fstream file;
	string filename;
	string keyfile;
	string input;
	Cipher c;

        cout << "Initializing 3dCipher Interface..." << endl;

	cout << "Please choose an option: " << endl;

	cout << "1. Generate Key" << endl;
        cout << "2. Encrypt" << endl;
        cout << "3. Decrypt" << endl;
        int option;
        cin >> option;

	switch (option) {
		case 1:
			{
			cout << "Please input the number of rotations to generate: ";
			int rotations;
			cin >> rotations;
			if (rotations <= 0) {
				cout << "Invalid number of rotations." << endl;
				return 1;
			}
			cout << "Generating key with " << rotations << " rotations" << endl;
			c.generateKey(rotations);
			cout << "Key generated!" << endl;
			}
			break;
		case 2:
			{
			string message = "Please input the name of the file to be encrypted: ";
			cout << message << endl;
			cin >> filename;

			file.open(filename, ios::in);
			if (!file) {
				cout << "File not found." << endl;
				file.close();
				return 1;
			}

			cout << "Please input the name of the key file: ";
			cin >> keyfile;

			if (!c.importKey(keyfile)) {
				cout << "Error: Invalid key file." << endl;
				file.close();
				return 1;
			}

			// Write contents of file to string
			string line;
			while (getline(file, line)) {
				input += line + "\n";
			}

			cout << input << endl;
			c.message = input;
			c.generateCubes(input);

			string encrypted = c.encrypt();
			cout << "Your encrypted message is: " << encrypted << endl;
			}
			break;
		case 3:	
			{
			string message = "Please input the name of the file to be decrypted: ";
			cout << message << endl;
			cin >> filename;

			file.open(filename, ios::in);
			if (!file) {
				cout << "File not found." << endl;
				file.close();
				return 1;
			}

			cout << "Please input the name of the key file: ";
			cin >> keyfile;

			if (!c.importKey(keyfile)) {
				cout << "Error: Invalid key file." << endl;
				file.close();
				return 1;
			}

			// Write contents of file to string
			string line;
			while (getline(file, line)) {
				input += line + "\n";
			}

			cout << input << endl;
			c.message = input;
			c.generateCubes(input);

			string decrypted = c.decrypt();
			cout << "Your decrypted message is: " << decrypted << endl;

			}
			break;
		default:
			{
			cout << "Invalid option" << endl;
			}
			break;
	}


	file.close();
        return 0;

}
