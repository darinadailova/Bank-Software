/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Darina Dailova
* @idnumber 62583
* @compiler VC
*
* <Main file>
*
*/

#include <iostream>
#include "Header.h"
#include <fstream>
#include <vector>

int main() {

	Account account;
	
	std::ifstream file;
	file.open("users.txt", std::fstream::in);

	if (!file.is_open()) {
		std::cout << "We are experiencing some technical difficulties. Please try again later!\n";
	}

	if (file.is_open()) {
		//read all information from the file and store it in vector
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