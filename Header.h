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
* <Header file>
*
*/

#pragma once
#include <vector>
#include <string>

class Account
{
	std::string m_username;
	std::string m_password;
	std::string m_currentLine;

public:
	double m_balance;
	std::vector<std::string>userInformation;
	void startMenu();
	void login();
	void Register();
	void saveChangesToFile();
	void mainMenu();
	void deposit();
	void withdraw();
	void cancelAccount();
	void transfer();
	void transferMoney(std::string line, int find1, double moneyTotransfer);
};

void intro();
bool checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(std::string&);
bool usernameValidation(std::string&);
bool passwordValidation(std::string&);
void RoundingNumberToTwoDecimalPlaces(double&);