#include <iostream>
#include "Header.h"
#include <fstream>
#include <vector>

int main() {

	Account account;
	
	std::ifstream file;
	file.open("users.txt", std::fstream::in);

	if (!file.is_open()) {
		std::cout << "Please try again later!\n";
	}

	if (file.is_open()) {

		std::string line;
		while (std::getline(file, line)) {
			account.userInformation.push_back(line);
		}
	}

	file.close();

	intro();
	account.startMenu();

	return 0;
}