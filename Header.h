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
* <File with functions declarations>
*
*/

#pragma once
#include <vector>
#include <string>

class Account
{//private members of the class
	std::string m_username;
	std::string m_password;
	std::string m_currentLine;

public:

	double m_balance;
	std::vector<std::string>userInformation;//vector that stores all of the information from "users.txt"
	void startMenu();//function to print start menu
	void login();//function for login
	void Register();//function for signup
	bool isUsernameAvailable(const std::string&);
	void saveChangesToFile();//function to save the changes we have made
	void mainMenu();//function to print main menu
	void deposit();//function for depositing money to account
	void withdraw();//function for withdrawing money from account
	void cancelAccount();//function for deleting account
	void transfer();//function for transfering money from one account to another
	void transferMoney(const std::string&, const int&, const double&);//function to make the transfer
	void modifyAccount();
};

void intro();
bool checkForLowerAndUpperLetterSymbolInPasswordAndLenghtOfPassword(const std::string&);
bool usernameValidation(const std::string&);
bool passwordValidation(const std::string&);
void RoundingNumberToTwoDecimalPlaces(double&);
std::string hashPassword(const std::string&);