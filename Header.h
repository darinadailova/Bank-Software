#pragma once

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
	void cancelAccount();
	void deposit();
	void mainMenu();
	void withdraw();
	void saveChangesToFile();
	void deleteAccount();
};

void intro();
bool checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(std::string&);
bool usernameValidation(std::string&);
bool passwordValidation(std::string&);