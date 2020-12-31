#include<iostream>
#include<fstream>
#include<string>

class Account
{
	std::string username;
	std::string password;
	std::string line;
	int find2;

public:
	double balance;
	void startMenu();
	void login();
	void Register();
	void quit();
	void cancelAccount();
	void deposit();
};

void Account::startMenu() {
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
			Register();
			break;
		case 'Q':

			break;
		default:
			std::cout << "\n\n\nPlease select L, R or Q\n";
		}
		std::cin.ignore();
		std::cin.get();
	} while (choice != 'L' && choice != 'R' && choice != 'Q');
}

void Account::login()
{
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
		while (getline(file, line)) {
			int find1 = line.find(':');
			for (int i = find1; i < line.size(); i++) {
				if (line[i] == ':') {
					find2 = i;
				}
			}
			if (username == line.substr(0, find1) && password == line.substr(find1 + 1, ((find2 - find1) - 1))) {
				std::cout << "Login was successful\n";
				std::string temp = line.substr(find2 + 1, line.size());
				balance = stod(temp);
				break;
			}
		}
	}

	file.close();
	
}

void Account::Register() {
	std::cout << "Please enter username: \n";
	std::cin >> username;
	std::cout << "Please enter password: \n";
	std::cin >> password;
	balance = 0;
}

void Account::quit() {
	
	std::string temp = std::to_string(balance);
	line.replace(find2, line.size(), temp);
}

void Account::cancelAccount() {

	std::cout << "Please enter your password: \n";
	std::string temp;
	std::cin >> temp;
	if (temp == password && balance == 00) {
		//delete account
		startMenu();
	}
}

void Account::deposit() {

	std::cout << "Please enter amount: \n";
	double amount;
	std::cin >> amount;
	balance += amount;
}


void intro() {

	std::cout << "=================================\n";
	std::cout << "\t     BANKING\n\n";
	std::cout << "\t    SOFTWARE\n\n";
	std::cout << "\tMADE BY: Darina Dailova\n\n";
	std::cout << "=================================\n\n";
	std::cin.get();
}

int main() {

	intro();
	Account account;
	account.startMenu();

	char choice;

	do {
		system("cls");
		std::cout << "=================================\n";
		std::cout << "\t   MAIN MENU\n\n";
		std::cout << "You have " << account.balance << " BGN. Choose one of the following options:\n\n";
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
			account.cancelAccount();
			break;
		case 'D':
			account.deposit();
			break;
		case 'L':
			account.startMenu();
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