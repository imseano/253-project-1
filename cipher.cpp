#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "quaternion.h"

using namespace std;

// Cube size of n x n x n
#define CUBE_SIZE 3

class Cube {
	public:
		vector<vector<vector<char>>> cube;
                Cube(vector<vector<vector<char>>> cube) {
                        this->cube = cube;
                }
		Cube() {
			vector<vector<vector<char>>> cube(CUBE_SIZE, vector<vector<char>>(CUBE_SIZE, vector<char>(CUBE_SIZE, ' ')));
			this->cube = cube;
		}

		vector<vector<char>>& operator[](int index) {
                        return cube[index];
                }
};

class Cipher {
	public:
	string message;
	vector<Quaternion> key;
	vector<Cube> cubes;

	Cipher(string message) {
                this->message = message;
        }

	void generateCubes(string message) {
		int cubeVolume = CUBE_SIZE;
		for (int i = 0; i < CUBE_SIZE - 1; i++) {
			cubeVolume *= CUBE_SIZE;
		}
		// Always round up cube number
		int numCubes = ceil((float) message.length() / cubeVolume);
		int messageIndex = 0;

		//cout << message << " " << numCubes << endl;
		for (int num = 0; num < numCubes; num++) {
			Cube cube;
			cubes.push_back(cube);
			for (int i = 0; i < CUBE_SIZE; i++) {
				for (int j = 0; j < CUBE_SIZE; j++) {
					for (int k = 0; k < CUBE_SIZE; k++) {
						if (messageIndex < message.length()) {
							//cout << "Storing " << message[messageIndex] << " in Cube " << num << " " << i << " " << j << " " << k << endl;
							//cout << message[messageIndex] << endl;
							cubes[num][i][j][k] = message[messageIndex];
						} else {
							cubes[num][i][j][k] = '\x1F';
						}
						messageIndex++;
					}
				}
			}
		}
		printCubes();
        }

	void printCubes() {
		for (int num = 0; num < cubes.size(); num++) {
                        cout << "Cube " << num << endl;
                        for (int i = 0; i < CUBE_SIZE; i++) {
                                for (int j = 0; j < CUBE_SIZE; j++) {
                                        for (int k = 0; k < CUBE_SIZE; k++) {
                                                cout << cubes[num][i][j][k] << " ";
                                        }
                                        cout << endl;
                                }
                        }
                }
		cout << readStringFromCubes() << endl;
	}

	void applyRotation(Quaternion q) {

		
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

	string readStringFromCubes() {
		string message = "";
		for (int num = 0; num < cubes.size(); num++) {
                        for (int i = 0; i < CUBE_SIZE; i++) {
                                for (int j = 0; j < CUBE_SIZE; j++) {
                                        for (int k = 0; k < CUBE_SIZE; k++) {
						if (cubes[num][i][j][k] != '\x1F') {  
							message += cubes[num][i][j][k];
						}
                                        }
                                }
                        }
                }
                return message;
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
