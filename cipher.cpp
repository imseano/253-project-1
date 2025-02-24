#include <cmath>
#include <queue>
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

	Cipher() {
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
		//printCubes();
		//Quaternion q = Quaternion(0.707, 0.707, 0, 0);
		//Quaternion q1 = Quaternion(0, 0, 1, 0);
		//applyRotation(q);
		//applyRotation(q1);

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
		cout << readStringFromCubes(false) << endl;
	}

	void applyRotation(Quaternion q) {
		cout << q.x << " " << q.y << " " << q.z << " " << q.w << " is the rotation" << endl;
		vector<Cube> cubesTemp = cubes;
		Quaternion qInverse = q.inverse();
		for (int num = 0; num < cubesTemp.size(); num++) {
                        for (int i = 0; i < CUBE_SIZE; i++) {
				for (int j = 0; j < CUBE_SIZE; j++) {
					for (int k = 0; k < CUBE_SIZE; k++) {
						Quaternion init = Quaternion(i, j, k, 0);
						Quaternion final = q * init * qInverse;
						int x = round(final.x);
						int y = round(final.y);
						int z = round(final.z);

						// Wrap around vector
						x = (x + CUBE_SIZE) % CUBE_SIZE;
						y = (y + CUBE_SIZE) % CUBE_SIZE;
						z = (z + CUBE_SIZE) % CUBE_SIZE;
						//cout << init.x << " " << init.y << " " << init.z << " " << init.w << " rotates to " << x << " " << y << " " << z << endl;

					cubesTemp[num][x][y][z] = cubes[num][i][j][k];
					}
				}
			}
		}
		cubes = cubesTemp;
		//printCubes();
		
	}

	// Key generation code assisted by ChatGPT
	//
	// Predefined set of valid rotation quaternions (representing 90°, 180°, and 270° rotations)

	vector<Quaternion> predefinedQuaternions = {
	    // 90° rotations around primary axes
	    Quaternion(0.707, 0.707, 0, 0),  // X+ (Right turn)
	    Quaternion(0.707, -0.707, 0, 0), // X- (Left turn)
	    Quaternion(0.707, 0, 0.707, 0),  // Y+ (Up turn)
	    Quaternion(0.707, 0, -0.707, 0), // Y- (Down turn)
	    Quaternion(0.707, 0, 0, 0.707),  // Z+ (Clockwise front turn)
	    Quaternion(0.707, 0, 0, -0.707), // Z- (Counterclockwise front turn)

	    // 180° rotations around primary axes
	    Quaternion(0, 1, 0, 0),  // X (Flip Right-Left)
	    Quaternion(0, 0, 1, 0),  // Y (Flip Up-Down)
	    Quaternion(0, 0, 0, 1),  // Z (Flip Front-Back)

	    // 120° rotations around the cube's diagonal axes
	    Quaternion(0.5, 0.5, 0.5, 0.5),   // (1, 1, 1) Axis (120°)
	    Quaternion(0.5, -0.5, -0.5, -0.5), // (1, 1, 1) Axis (240°)
	    Quaternion(0.5, -0.5, 0.5, 0.5),   // (-1, 1, 1) Axis (120°)
	    Quaternion(0.5, 0.5, -0.5, -0.5)   // (-1, 1, 1) Axis (240°)
	};

	// Generate key: select random quaternions from the predefined set
	vector<Quaternion> generateKey(int numQuaternions) {
	    vector<Quaternion> temp;
	    srand(static_cast<unsigned int>(time(0)));

	    for (int i = 0; i < numQuaternions; i++) {
		// Select a random quaternion from the predefined set
		int randomIndex = rand() % predefinedQuaternions.size();
		temp.push_back(predefinedQuaternions[randomIndex]);
	    }

	    string tempFilename;

	    cout << "Please enter a filename to save the key: ";
	    cin >> tempFilename;

	    exportKey(temp, tempFilename);

	    return temp;
	}

	// Export key to a file
	void exportKey(const vector<Quaternion>& key, string filename) {
	    ofstream file(filename);
	    if (!file) {
		cout << "Error: Could not open the file for writing!" << endl;
		return;
	    }

	    for (int i = 0; i < key.size(); i++) {
		file << key[i].x << " " << key[i].y << " " << key[i].z << " " << key[i].w << endl;
	    }

	    cout << "Key saved to " << filename << endl;
	}

	// Import key from a file, returns 0 if invalid
	bool importKey(string filename) {
	    key.clear();
	    fstream file(filename);
	    if (!file.is_open()) {
		cout << "Error: Could not open the file for reading!" << endl;
		return false;
	    }

	    Quaternion q;
	    while (file >> q) {
		key.push_back(q);
	    }

	    // Check if the key is empty (no valid quaternion data was found)
	    if (key.empty()) {
		cout << "Error: No valid quaternions found in the file." << endl;
		return false;
	    }

	    file.close();
	    return true;
	}

	/**
	 * Note: allowPlaceholders flag is used to remove any placeholder characters from the message.
	 *       This is only used for printing and decryption, as encryption needs placeholders.
	 */
	string readStringFromCubes(bool allowPlaceholders) {
		string message = "";
		for (int num = 0; num < cubes.size(); num++) {
                        for (int i = 0; i < CUBE_SIZE; i++) {
                                for (int j = 0; j < CUBE_SIZE; j++) {
                                        for (int k = 0; k < CUBE_SIZE; k++) {
						// Only remove placeholder if flag is set
						if (!allowPlaceholders) {
							if (cubes[num][i][j][k] != '\x1F') {  
								message += cubes[num][i][j][k];
							}
						} else {
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
		vector<Quaternion> qStack;
		for (Quaternion q : key) {
			qStack.push_back(q);
		}
		while (!qStack.empty()) {
                        Quaternion q = qStack.back();
                        qStack.pop_back();
			applyRotation(q);
                }
		encryption = readStringFromCubes(true);
		file << encryption;
		return encryption;
	}

	string decrypt() {
		string decryption = message;
		ofstream file("decrypted.txt");
		cout << "I will decrypt the message" << endl;
		queue<Quaternion> qQueue;
		for (Quaternion q : key) {
			qQueue.push(q);
		}
		while (!qQueue.empty()) {
			Quaternion q = qQueue.front();
			qQueue.pop();
			applyRotation(q.inverse());
                }
		decryption = readStringFromCubes(false);
		file << decryption;
		return decryption;
	}
};
