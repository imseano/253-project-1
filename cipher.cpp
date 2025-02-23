#include <iostream>
#include <fstream>
#include <vector>
#include "quaternion.h"

using namespace std;

// Cube size of n x n x n
#define CUBE_SIZE 3

class Cipher {
	public:
	string message;
	vector<Quaternion> key;

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

	vector<Quaternion> generateKey() {
		vector<Quaternion> temp;
		return temp;
	}

	void exportKey(string filename) {
		ofstream file(filename);
		for (int i = 0; i < key.size(); i++) {
			file << key[i].x << " " << key[i].y << " " << key[i].z << " " << key[i].w << endl;
		}
		cout << "Key saved to " << filename << endl;
	}

	void importKey(string filename) {
		key.clear();
		fstream file(filename);
                while (!file.eof()) {
                        Quaternion q;
                        file >> q.x >> q.y >> q.z >> q.w;
                        key.push_back(q);
                }
		file.close();
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
