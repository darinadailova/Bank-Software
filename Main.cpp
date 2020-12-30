#include<iostream>
#include<fstream>
#include<string>

void intro() {

	std::cout << "=================================\n";
	std::cout << "\t     BANKING\n\n";
	std::cout << "\t    SOFTWARE\n\n";
	std::cout << "\tMADE BY: Darina Dailova\n\n";
	std::cout << "=================================\n\n";
	std::cin.get();
}

void login() {
	
	std::ifstream file;
	file.open("users.txt", std::fstream::in);
	
	if (!file.is_open()) {
		std::cout << "Please try again later!\n";
	}

	if (file.is_open()) {
		std::string username;
		std::string password;
		std::cout << "Please enter username:\n";
		std::cin >> username;
		std::cout << "Please enter password:\n";
		std::cin >> password;
		std::string line;
		while (std::getline(file, line)) {
			unsigned int find1 = line.find(':');
			int find2 = -1;
			for (int i = find1; i < line.size(); i++) {
				if (line[i] == ':') {
					find2 = i;
				}
			}
			if (username == line.substr(0, find1) && password == line.substr(find1 + 1, ((find2 - find1) - 1))) {
				std::cout << "Login was successful\n";
			}
		}
	}

	file.close();
}

int main() {

	intro();
	char choice = 'a';
	
	do {
		system("cls");
		std::cout << "=================================\n";
		std::cout << "\t   START MENU\n\n";
		std::cout << "L - login\n\n";
		std::cout << "R - register\n\n";
		std::cout << "Q - quit\n\n";
		std::cout << "=================================\n\n";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case 'L':
			login();
			break;
		case 'R':

			break;
		case 'Q':

			break;
		default:
			std::cout << "\n\n\nPlease select L, R or Q\n";
		}
		std::cin.ignore();
		std::cin.get();
	} while (choice != 'L' && choice != 'R' && choice != 'Q');

	do {
		system("cls");
		std::cout << "=================================\n";
		std::cout << "\t   MAIN MENU\n\n";
		std::cout << "C - cancel account\n\n";
		std::cout << "D - deposit\n\n";
		std::cout << "L - logout\n\n";
		std::cout << "T - transfer\n\n";
		std::cout << "W - withdraw\n\n";
		std::cout << "=================================\n\n";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case 'C':
			break;
		case 'D':

			break;
		case 'L':

			break;
		case 'T':
			break;
		case 'W':
			break;
		default:
			std::cout << "\n\n\nPlease select C, D, L, T or W\n";
		}
		std::cin.ignore();
		std::cin.get();
	} while (choice != 'C' && choice != 'D' && choice != 'L' && choice != 'T' && choice != 'W');

	return 0;
}