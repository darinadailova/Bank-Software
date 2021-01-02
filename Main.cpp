#include<iostream>
#include<fstream>
#include<string>
#include <cstdio>
#include<cctype>

class Account
{
	std::string m_username;
	std::string m_password;
	std::string m_currentLine;

public:
	double m_balance;
	void startMenu();
	void login();
	void Register();
	void quit();
	void cancelAccount();
	void deposit();
	void changeBalance();
	void deleteAccount();
	void createAccount();
	void mainMenu();
	void withdraw();
};

void intro() {

	std::cout << "=================================\n";
	std::cout << "\t     BANKING\n\n";
	std::cout << "\t    SOFTWARE\n\n";
	std::cout << "\tMADE BY: Darina Dailova\n\n";
	std::cout << "=================================\n\n";
	std::cin.get();
}

bool checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(std::string& str) {

	int size = str.size();
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (isupper(str[i])) {
			count++;
		}
		if (islower(str[i])) {
			count++;
		}
		if (str[i] > 34 && str[i] < 39) {
			count++;
		}
		if (str[i] == 33 || str[i] == 64 || str[i] == 94 || str[i] == 42) {
			count++;
		}
	}

	if (count > 2 && size > 4) {
		return true;
	}

	return false;
}

bool usernameAndPasswordValidation(std::string& str) {
	int strSize = str.size();
	int count = 0;

	for (int i = 0; i < strSize; i++) {

		if ((str[i] > 96 && str[i] < 123) || (str[i] > 64 && str[i] < 91)) {
			count++;
		}

		if (str[i] > 34 && str[i] < 39) {
			count++;
		}

		if (str[i] == 33 || str[i] == 64 || str[i] == 94 || str[i] == 42) {
			count++;
		}
	}

	if (count == strSize) {
		return true;
	}

	return false;
}

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
			std::cout << "Thanks for using our bank! Have a nice day!\n";
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
		std::string line;

		std::cout << "Please enter username:\n";
		std::cin >> username;
		std::cout << "Please enter password:\n";
		std::cin >> password;
		bool flag = false;

		while (std::getline(file, line)) {
			int find1 = line.find(':');
			int find2 = -1;
			for (int i = find1; i < line.size(); i++) {
				if (line[i] == ':') {
					find2 = i;
				}
			}

			if (username == line.substr(0, find1) && password == line.substr(find1 + 1, line.size() - find2)) {

				m_username = line.substr(0, find1);
				m_password = line.substr(find1 + 1, line.size() - find2);
				m_currentLine = line;
				std::cout << "Login was successful\n";
				std::string temp = line.substr(find2 + 1, line.size());
				m_balance = stod(temp);
				flag = true;
				break;
			}
		}

		if (!flag) {
			std::cout << "Wrong username or password. Please try again later!\n";
			system("pause");
			startMenu();
		}
	}

	file.close();
}

void Account::Register() {

	std::cout << "For the username and password you can only use latin lettes and these symbols:  !@#$%^&*\n";
	std::cout << "Please enter username: \n";
	std::cin >> m_username;

	while (!usernameAndPasswordValidation(m_username)) {
		std::cout << "You used incorrect symbol! Please try again: \n";
		std::cin >> m_username;
	}

	std::cout << "Please enter password: \n";
	std::cout << "The password should have 1 uppercase letter, 1 lowercase letter, 1 symbol and it should be at least 5 characters!\n";
	std::cin >> m_password;
	while (!usernameAndPasswordValidation(m_password) || !checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(m_password)) {
		std::cout << "Password is incorrect. Try again: \n";
		std::cin >> m_password;
	}

	m_balance = 0;
	std::cout << "Registration complete!\n";
	createAccount();
}

void Account::createAccount() {

	std::ifstream file("users.txt");
	std::ofstream tempFile("temp.txt");
	std::string line;

	while (file >> line) {
		tempFile << line << '\n';
	}

	tempFile << m_username << ':' << m_password << ':' << m_balance;

	file.close();
	tempFile.close();

	std::remove("users.txt");
	int result = std::rename("temp.txt", "users.txt");
}

void Account::quit() {


}

void Account::cancelAccount() {

	std::cout << "Please enter your password: \n";
	std::string temp;
	std::cin >> temp;

	if (temp == m_password && m_balance == 0) {
		deleteAccount();
		startMenu();
	}
}

void Account::deposit() {

	std::cout << "Please enter amount: \n";
	double amount;


	std::cin >> amount;
	m_balance += amount;
	std::cout << "You now have " << m_balance << " BGN\n";
	changeBalance();
}

void Account::changeBalance() {

	std::ifstream file("users.txt");
	std::ofstream tempFile("temp.txt");
	std::string line;

	while (file >> line) {
		if (line == m_currentLine) {
			tempFile << m_username << ':' << m_password << ':' << m_balance << '\n';
		}
		else {
			tempFile << line << '\n';
		}
	}
	file.close();
	tempFile.close();

	std::remove("users.txt");
	std::rename("temp.txt", "users.txt");
}

void Account::deleteAccount() {

	std::ifstream file("users.txt");
	std::ofstream tempFile("temp.txt");
	std::string line;
	while (file >> line) {
		if (line != m_currentLine) {
			tempFile << line << '\n';
		}
	}
	file.close();
	tempFile.close();

	std::remove("users.txt");
	std::rename("temp.txt", "users.txt");

	startMenu();
}

void Account::mainMenu() {
	char choice;

	do {
		system("cls");
		std::cout << "=================================\n";
		std::cout << "\t   MAIN MENU\n\n";
		std::cout << "You have " << m_balance << " BGN. Choose one of the following options:\n\n";
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
			cancelAccount();
			mainMenu();
			break;
		case 'D':
			deposit();
			mainMenu();
			break;
		case 'L':
			startMenu();
			break;
		case 'T':
			mainMenu();
			break;
		case 'W':
			withdraw();
			mainMenu();
			break;
		default:
			std::cout << "\n\n\nPlease select C, D, L, T or W\n";
		}
		std::cin.ignore();
		std::cin.get();
	} while (choice != 'C' && choice != 'D' && choice != 'L' && choice != 'T' && choice != 'W');

}

void Account::withdraw() {

	std::cout << "How much you would like to withdraw?\n";
	double withdrawAmount;
	std::cin >> withdrawAmount;

	double divide = m_balance - withdrawAmount;
	if (divide >= 0) {
		m_balance = divide;
		std::cout << "You have " << m_balance << " BGN left.\n";
		system("pause");
	}
	else if (divide < 0 && divide >= -10000) {
		std::cout << "To withdraw " << withdrawAmount << " BGN. You have to get overdraft of " << withdrawAmount - m_balance << " BGN.\n";
		m_balance = divide;
	}
	else {
		std::cout << "You can't get that amount! Plase try again later!\n";
	}

	changeBalance();
}

int main() {

	intro();
	Account account;
	account.startMenu();
	account.mainMenu();

	return 0;
}