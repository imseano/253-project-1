#include <iostream>
#include <fstream>
#include "quaternion.h"

using namespace std;

class Cipher {
	public:
	string message;

	Cipher(string message) {
                this->message = message;
		Quaternion q(1, 1, 1, 1);
		Quaternion q2(2, 2, 2, 2);
		cout << q.x << " " << q.y << " " << q.z << " " << q.w << endl;
		q = q*3;
		cout << q.x << " " << q.y << " " << q.z << " " << q.w << endl;
		q = q*q2;
		cout << q.x << " " << q.y << " " << q.z << " " << q.w << endl;
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
