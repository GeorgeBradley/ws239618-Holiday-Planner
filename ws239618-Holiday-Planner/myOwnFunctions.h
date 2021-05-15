#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cctype>
#include <fstream> //This allows for input / output to an external textfile
// requires '#include <limits>'
#include <sstream>
#include <conio.h>
#include <algorithm>
#include <iomanip>

void displayInvalidCommandMessage();
//Used for ensuring what user has inputted isn't a disproportinate amount
void warningMessage(std::string sMessage);
bool isSingleAlphaCharacter(std::string sValue);
bool boundaryCheckValueIsValid(int iValue, int iMin, int iMax); //overloaded function to handle ints
bool boundaryCheckValueIsValid(double dValue, double dMin, double dMax); //overloaded function to handle doubles
bool confirmYesOrNo(std::string sMessage);
//Overloaded functions for various types of input
void messageAndInput(std::string prompt, std::string* value);
void messageAndInput(std::string prompt, std::size_t stIndex, std::string* value);//Used to display the '£' to demonstrate it's currency
void messageAndInput(std::string prompt, std::size_t* iIndex);
void messageAndInput(std::string prompt, int* value);
void messageAndInput(std::string prompt, double* value);
void messageAndInput(std::string prompt, unsigned char* value);
bool isADouble(const std::string& s);
bool enterDouble(std::string sMessage, std::string sString, double& dValue);
void nothingToDisplayMessage();
bool isInputValid();
bool isStringCharacterAllowed(std::string sValue);
bool isInputANumber(std::string sLine, double* dValue);
bool isInputANumber(std::string sLine, int* iValue);
bool isStringLengthValid(std::string sItemName, const std::size_t stLengthMinimum, const std::size_t stLengthMaximum);
void performInvalidOperation();
void clearTextFileContents(std::string inputFilePath);
void message(std::string sMessage);
void errorMessage(std::string sMessage);
void successMessage(std::string sMessage);
bool enterInteger(std::string sMessage, std::string sOption, int& iOption, int iMenuItemSize);
bool checkValueAndConvert(std::string sValue, int* iValue);
bool isNumber(std::string sValue);
bool convertStringToInt(std::string sValue, int* iValue);
template<typename T> void printElement(T t, const int& width)
{
	const char separator = ' ';
	std::cout << std::left << std::setw(width) << std::setfill(separator) << t;
}
std::string stringToUpper(std::string sString);

//This function converts a double to a string, precisioning it to whatever number is passed in through the int parameter
//I'm using a template here incase the datatype changes
template <typename T>
std::string toStringWithPrecision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

