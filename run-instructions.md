# How to Run
## Makefile
The project can be built using `make` command in the root of the project. You need to run just ``make all`` the first time you build this, and``make clean && make all`` will rebuild the entire application if any changes are made. 
## From Scratch
If the makefile does not work, then you can build it with the following commands:
```
g++ -Wall -g -c 3dCubeCipherMain.cpp -o 3dCubeCipherMain.o
g++ -Wall -g -c quaternion.cpp -o quaternion.o
g++ -Wall -g -o ./cubecipher 3dCubeCipherMain.o quaternion.o
```
## How to use
The application offers three choices when run:
```
Please choose an option:
1. Generate Key
2. Encrypt
3. Decrypt
```
First, you must generate a key in order to encrypt and decrypt plaintext. The application will ask you for a number of rotations. Think of this as your key size. 
After generating a key and saving it as a file, you may now use that key freely to encrypt and decrypt plaintext.


