#include <iostream>

char* encrypt(char* message);
char* decrypt(char* message);

int main() {
        std::cout << "Initializing Cryptography Test..." << std::endl << "hi" << std::endl;

	char* message = "Hello this is a test";
	std::cout << message << std::endl;

	char* encrypted = encrypt(message);
        std::cout << encrypted << std::endl;

	char* decrypted = decrypt(encrypted);
	std::cout << decrypted << std::endl;

        return 0;
}

char* encrypt(char* message) {
	std::cout << "I will encrypt the message" << std::endl;
	return message;
}

char* decrypt(char* message) {
        std::cout << "I will decrypt the message" << std::endl;
        return message;
}
