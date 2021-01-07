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
* <file with helper functions>
*
*/

#include <iostream>
#include "Header.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <cctype>
#include <vector>

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
	bool upperLetterFlag = false;
	bool lowerLetterFlag = false;
	bool symbolFlag = false;

	for (int i = 0; i < size; i++) {
		//checks for uppercase letters
		if (isupper(str[i])) {
			upperLetterFlag = true;
		}
		//checks for lowercase letters
		if (islower(str[i])) {
			lowerLetterFlag = true;
		}
		//checks for symbols - #, $, % and &
		if (str[i] >= '#'  && str[i] <= '&') {
			symbolFlag = true;
		}
		
		if (str[i] == '!' || str[i] == '@' || str[i] == '^' || str[i] == '*') {
			symbolFlag = true;
		}
	}
	//the password should be atleast 5 symbols and has to have 1 uppers letter, 1 lower letter and symbol
	if (upperLetterFlag && lowerLetterFlag && symbolFlag && size > 4) {
		return true;
	}

	return false;
}

bool usernameValidation(std::string& str) {

	int strSize = str.size();
	int count = 0;

	for (int i = 0; i < strSize; i++) {
		//checks  for upper and lowercase letters
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			count++;
		}
		////checks for symbols - #, $, % and &
		if (str[i] >= '#' && str[i] <= '&') {
			count++;
		}
		
		if (str[i] == '!' || str[i] == '@' || str[i] == '^' || str[i] == '*') {
			count++;
		}
	}

	//checks if string size is equal to the counter so we can see if the input is correct
	if (count == strSize) {
		return true;
	}

	return false;
}

bool passwordValidation(std::string& str) {

	int strSize = str.size();
	int count = 0;

	for (int i = 0; i < strSize; i++) {

		//checks  for upper and lowercase letters
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
			count++;
		}
		//checks for symbols - #, $, % and &
		if (str[i] >= '#' && str[i] <= '&') {
			count++;
		}
		
		if (str[i] == '!' || str[i] == '@' || str[i] == '^' || str[i] == '*') {
			count++;
		}
		//checks for numbers in the password
		if (isdigit(str[i])) {
			count++;
		}
	}

	if (count == strSize) {
		return true;
	}

	return false;
}

void RoundingNumberToTwoDecimalPlaces(double& num) {

	std::string numStr = std::to_string(num);

	for (int i = 0; i < numStr.size(); i++) {
		if (numStr[i] == '.') {

			std::string temp;
			temp = numStr.substr(0, i + 3);
			num = stod(temp);
		}
	}
}

std::string hashPassword(std::string& password) {

	int size = password.size();
	std::vector<char>arr;//vector to store the hashed password

	for (int i = 0; i < size; i++) {
		//generates a random string that will be used as hashed password
		if (password[i] > 34 && password[i] < 39) {
			arr.push_back(password[i] + 6);
		}

		if (password[i] == 33 || password[i] == 64 || password[i] == 94 || password[i] == 42) {
			arr.push_back(password[i] + 10);
		}

		if (password[i] > 96 && password[i] < 110) {
			arr.push_back(password[i] + 7);
		}

		if (password[i] > 109 && password[i] < 123) {
			arr.push_back(password[i] + 4);
		}

		if (password[i] > 64 && password[i] < 71) {
			arr.push_back(password[i] + 15);
		}

		if (password[i] > 70 && password[i] < 91) {
			arr.push_back(password[i] + 20);
		}

	}
	//converts char array to string
	std::string hashedPassword(arr.begin(), arr.end());

	return hashedPassword;
}

void Account::startMenu() {

	std::cout << "=================================\n";
	std::cout << "\t   START MENU\n\n";
	std::cout << "L - login\n\n";
	std::cout << "R - register\n\n";
	std::cout << "Q - quit\n\n";
	std::cout << "=================================\n\n";
	std::cout << "Please choose an option:\n";

	char choice;
	std::cin >> choice;
	
	while (choice != 'L' && choice != 'R' && choice != 'Q') {
		std::cin >> choice;
	}

	if (choice == 'L') {
		login();
	}
	else if (choice == 'R') {
		Register();
	}
	else {
		std::cout << "Thanks for choosing our bank. Have a nice day!\n";
		saveChangesToFile();
		std::cin.ignore().get();	
	}
}

void Account::login()
{
	std::string username;
	std::string password;

	std::cout << "Please enter username:\n";
	std::cin >> username;
	std::cout << "Please enter password:\n";
	std::cin >> password;

	int size = userInformation.size();
	std::string line;
	bool flag = false;

	for (int i = 0; i < size; i++) {
		
		std::string line;
		line = userInformation[i];
		int find1 = line.find(':');
		int find2;
		//by finding the two ':' we can separate the line in 3 pieces - username, password and balance
		for (int i = find1 + 1; i < line.size(); i++) {
			if (line[i] == ':') {
				find2 = i;
			}
		}

		if (username == line.substr(0, find1) && hashPassword(password) == line.substr(find1 + 1, (find2 - find1) - 1)) {

			m_username = line.substr(0, find1);
			m_password = line.substr(find1 + 1, find2 - find1 - 1);
			m_currentLine = line;
			std::cout << "Login was successful\n";
			std::string temp = line.substr(find2 + 1, line.size());
			m_balance = stod(temp);//converts string to double
			flag = true;
			m_currentLine = line;
			std::cin.ignore().get();
			mainMenu();
			break;
		}


	}

	if (!flag) {
		std::cout << "Wrong username or password. Please try again later!\n";
		std::cin.ignore().get();
		startMenu();
	}
}

bool Account::isUsernameAvailable(std::string username) {

	int size = userInformation.size();
	for (int i = 0; i < size; i++) {
		std::string line = userInformation[i];
		int find = line.find(':');

		if (username == line.substr(0, find)) {
			return false;
		}
	}

	return true;
}

void Account::Register() {

	std::cout << "For the username and password you can only use latin lettes and these symbols:  !@#$%^&*\n";
	std::cout << "Please enter username: \n";
	std::cin >> m_username;

	while (!usernameValidation(m_username)) {
		std::cout << "You used incorrect symbol! Please try again: \n";
		std::cin >> m_username;
	}

	while (!isUsernameAvailable(m_username)) {
		std::cout << "That username is already taken please choose new one:\n";
		std::cin >> m_username;
	}

	std::cout << "Please enter password: \n";
	std::cout << "The password should have 1 uppercase letter, 1 lowercase letter, 1 symbol and it should be at least 5 characters!\n";
	std::cin >> m_password;
	while (!passwordValidation(m_password) || !checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(m_password)) {
		std::cout << "Password is incorrect. Try again: \n";
		std::cin >> m_password;
	}

	m_balance = 0;
	m_password = hashPassword(m_password);
	std::cout << "Registration complete!\n";
	//storing the new information in vector
	std::string line;
	line.append(m_username);
	line.append(":");
	line.append(m_password);
	line.append(":");
	line.append("0");
	m_currentLine = line;
	userInformation.push_back(line);
	std::cin.ignore().get();
	mainMenu();
}

void Account::saveChangesToFile() {
	
	std::ifstream file("users.txt");
	file.close();
	std::remove("users.txt");

	std::ofstream tempFile("users.txt");
	if (!tempFile.is_open()) {
		std::cout << "The changes weren't save. Please try again later\n";
		std::cin.ignore().get();
	}

	if (tempFile.is_open()) {

		int size = userInformation.size();
		for (int i = 0; i < size; i++) {

			if (userInformation[i] != m_currentLine) {
				tempFile << userInformation[i] << '\n';
			}
			else {
				tempFile << m_username << ':' << m_password << ':' << m_balance << '\n';
			}
		}
	}

	tempFile.close();
}

void Account::mainMenu() {

	std::cout << "=================================\n";
	std::cout << "\t   MAIN MENU\n\n";
	std::cout << "You have " << m_balance << " BGN. Choose one of the following options:\n\n";
	std::cout << "C - cancel account\n\n";
	std::cout << "D - deposit\n\n";
	std::cout << "L - logout\n\n";
	std::cout << "T - transfer\n\n";
	std::cout << "W - withdraw\n\n";
	std::cout << "=================================\n\n";
	std::cout << "Please choose an option:\n";

	char choice;
	std::cin >> choice;

	while (choice != 'C' && choice != 'D' && choice != 'L' && choice != 'T' && choice != 'W') {
		std::cin >> choice;
	}

	if (choice == 'D') {
		deposit();
		mainMenu();
	}
	else if (choice == 'W') {
		withdraw();
		mainMenu();
	}
	else if (choice == 'C') {
		cancelAccount();
	}
	else if (choice == 'L') {
		startMenu();
	}
	else {
		transfer();
	}
}

void Account::deposit() {

	std::cout << "Please enter amount: \n";
	double amount;
	std::cin >> amount;
	RoundingNumberToTwoDecimalPlaces(amount);

	while (amount < 0) {
		std::cout << "Please enter positive number\n";
		std::cin >> amount;
	}
	m_balance += amount;
	std::cout << "You now have " << m_balance << " BGN\n";
	std::cin.ignore().get();
}

void Account::withdraw() {

	std::cout << "How much you would like to withdraw?\n";
	double withdrawAmount;
	std::cin >> withdrawAmount;
	RoundingNumberToTwoDecimalPlaces(withdrawAmount);

	while (withdrawAmount < 0) {
		std::cout << "Please enter positive number\n";
		std::cin >> withdrawAmount;
	}
	double difference = m_balance - withdrawAmount;
	if (difference >= 0) {
		std::cout << "You have " << difference << " BGN left.\n";
		m_balance = difference;
		std::cin.ignore().get();
	}
	else if (difference < 0 && difference >= -10000) {
		std::cout << "To withdraw " << withdrawAmount << " BGN. You have to get overdraft of " << withdrawAmount - m_balance << " BGN.\n";
		m_balance = difference;
		std::cin.ignore().get();
	}
	else {
		std::cout << "You can't get that amount!\n";
		std::cin.ignore().get();
	}
}

void Account::cancelAccount() {

	std::cout << "Please enter your password: \n";
	std::string temp;
	std::cin >> temp;
	//to cancel account you have to have 0 BGN int the account 
	if (hashPassword(temp) == m_password && m_balance == 0) {

		int size = userInformation.size();
		for (int i = 0; i < size; i++) {
		
			std::string line = userInformation[i];
			int find = line.find(':');
			std::string username = line.substr(0, find);
			if(username == m_username) {

				std::ifstream file("users.txt");
				file.close();
				std::remove("users.txt");

				std::ofstream tempFile("users.txt");
				if (!tempFile.is_open()) {
					std::cout << "The changes weren't save. Please try again later\n";
					std::cin.ignore().get();
				}

				if (tempFile.is_open()) {

					int size = userInformation.size();
					for (int i = 0; i < size; i++) {

						if (userInformation[i] != m_currentLine) {
							tempFile << userInformation[i] << '\n';
						}
					}
				}

				tempFile.close();
			}

		}
		std::cout << "Your account was deleted succesfully.\n";
		std::cin.ignore().get();
	}
	else if (temp != m_password) {
		std::cout << "Wrong password!\n";
		std::cin.ignore().get();
		mainMenu();
	}
	else if (temp == m_password && m_balance != 0) {
		std::cout << "To cancel account your balance should be 0!\n";
		std::cin.ignore().get();
		mainMenu();
	}
}

void Account::transfer() {

	std::cout << "How much money do you want to transfer?\n";
	double moneyTotransfer;
	std::cin >> moneyTotransfer;

	while (moneyTotransfer < 0) {
		std::cout << "Please enter positive number\n";
		std::cin >> moneyTotransfer;
	}
	
	RoundingNumberToTwoDecimalPlaces(moneyTotransfer);
	double difference = m_balance - moneyTotransfer;
	if (difference >= -10000) {

		if (difference < 0) {
			std::cout << "To transfer " << moneyTotransfer << " BGN. You have to get overdraft of " << moneyTotransfer - m_balance << std::endl;
			std::cin.ignore().get();
		}

		std::cout << "Please enter the username of recipient:\n";
		std::string searchedUsername;
		std::cin >> searchedUsername;
		bool flag = false;
		for (int i = 0; i < userInformation.size(); i++) {
			std::string line;
			line = userInformation[i];
			int find1 = line.find(':');
			if (line.substr(0, find1) == searchedUsername) {
				flag = true;
				transferMoney(line, find1, moneyTotransfer);
				break;
			}
		}
		if (!flag) {
			std::cout << "This account doesn't exists!\n";
			std::cin.ignore().get();
			mainMenu();
		}
	}
	else {
		std::cout << "You can't get that amount!\n";
		std::cin.ignore().get();
	}
}

void Account::transferMoney(std::string line, int find1, double moneyToTransfer) {

	int find2;
	for (int i = find1 + 1; i < line.size(); i++) {
		if (line[i] == ':') {
			find2 = i;
		}
	}
	std::string username = line.substr(0, find1);
	std::string password = line.substr(find1 + 1, find2 - find1 - 1);
	std::string balance = line.substr(find2 +1, line.size() - find2);
	double balanceNumber = stod(balance);
	balanceNumber += moneyToTransfer;

	std::string searchedAccount;
	searchedAccount.append(username);
	searchedAccount.append(":");
	searchedAccount.append(password);
	searchedAccount.append(":");
	searchedAccount.append(balance);

	std::ifstream file("users.txt");
	file.close();
	std::remove("users.txt");

	std::ofstream tempFile("users.txt");
	if (!tempFile.is_open()) {
		std::cout << "The transfer wasn't made. Please try again later\n";
		std::cin.ignore().get();
	}

	if (tempFile.is_open()) {
		m_balance -= moneyToTransfer;
		int size = userInformation.size();
		for (int i = 0; i < size; i++) {
			if (userInformation[i] != searchedAccount && userInformation[i] != m_currentLine) {
				tempFile << userInformation[i] << '\n';
			}
			if(userInformation[i] == searchedAccount) {
				tempFile << username << ':' << password << ':' << balanceNumber << '\n';
			}
			if (userInformation[i] == m_currentLine) {
				tempFile << m_username << ':' << m_password << ':' << m_balance << '\n';
			}
		}
		std::cout << "Transfer - complete!\n";
		std::cin.ignore().get();
	}

	tempFile.close();
}