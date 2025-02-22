#include <iostream>
#include <fstream>

using namespace std;
string encrypt(string message);
string decrypt(string message);

int main() {
	fstream file;
	string filename;
	string input, output;

        cout << "Initializing Cryptography Test..." << endl << "hi" << endl;

	string message = "Please input the name of the file to be encrypted: ";
	cout << message << endl;
	cin >> filename;

	file.open(filename, ios::in);
        if (!file) {
                cout << "File not found." << endl;
                return 1;
	}

	string line;

	while (getline(file, line)) {
		input += line + "\n";
        }

	cout << input << endl;

	string encrypted = encrypt(input);
        cout << "Your encrypted message is: " << encrypted << endl;

	string decrypted = decrypt(encrypted);
	cout << "Your decrypted message is: " << decrypted << endl;

	if (encrypted == decrypted) {
                cout << "Success!" << endl;
        }

        return 0;
}

string encrypt(string message) {
	string encryption = message;
	ofstream file("encrypted.txt");
	cout << "I will encrypt the message" << endl;
	file << encryption;
	return encryption;
}

string decrypt(string message) {
	string decryption = message;
	ofstream file("decrypted.txt");
        cout << "I will decrypt the message" << endl;
	file << decryption;
        return decryption;
}
