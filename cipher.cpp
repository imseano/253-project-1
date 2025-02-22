#include <iostream>
#include <fstream>

using namespace std;

class Cipher {
	public:
	string message;

	Cipher(string message) {
                this->message = message;
        }

	string encrypt() {
		string encryption = message;
		ofstream file("encrypted.txt");
		cout << "I will encrypt the message" << endl;
		file << encryption;
		return encryption;
	}

	string decrypt() {
		string decryption = message;
		ofstream file("decrypted.txt");
		cout << "I will decrypt the message" << endl;
		file << decryption;
		return decryption;
	}
};
