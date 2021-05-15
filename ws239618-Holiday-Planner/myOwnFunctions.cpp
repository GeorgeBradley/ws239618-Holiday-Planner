//  Functions.cpp
//  Sale System
//These functions are used throughout all cpp files
#include "myOwnFunctions.h"
//Clears all contents in the the text file.

std::string stringToUpper(std::string sString) {
	std::string toUpper = "";
	for (const unsigned char character : sString) {
		toUpper.push_back(std::toupper(character));
	}
	return toUpper;
}
bool confirmYesOrNo
(std::string sMessage) {
	do
	{
		std::string sAnswer = "";
		messageAndInput(sMessage, &sAnswer);
		if (isSingleAlphaCharacter(sAnswer))
		{
			if (sAnswer == "y")
			{
				return true;
			}
			else if (sAnswer == "n")
			{
				return false;
			}
			else
			{
				message("Sorry, we didn't quite catch that?\n");
		
			}
		}
	} while (true);
}
bool convertStringToInt(std::string sValue, int* iValue) {
	try
	{
		*iValue = stoi(sValue);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
bool enterDouble(std::string sMessage, std::string sString, double& dValue) {
	do
	{
		messageAndInput(sMessage, &sString);
		if (isADouble(sString))
		{
			dValue = stod(sString);
			return true;
		}
		else
		{
			errorMessage("Please enter a number e.g. 1000, 1000.54\n");
		}
	} while (true);
}
bool isADouble(const std::string& s)
{
	try
	{
		std::stod(s);
	}
	catch (...)
	{
		return false;
	}
	return true;
}
bool checkValueAndConvert(std::string sValue, int* iValue) {
	if (isNumber(sValue))
	{
		if (convertStringToInt(sValue, iValue))
		{
			return true;
		}
		return false;
	}
	return false;
}
bool isNumber(std::string sValue) {
	return !sValue.empty() && std::find_if(sValue.begin(), sValue.end(), [](auto character) {
		return !isdigit((unsigned char)character);
		}) == sValue.end();
}
bool enterInteger(std::string sMessage, std::string sOption, int& iOption, int iMenuItemSize) {
	do
	{
		messageAndInput
		(sMessage, &sOption);
		//checks if number is valid
		if (checkValueAndConvert(sOption, &iOption))
		{
			//boundary checking
			if (iOption >= 0 && iOption <= iMenuItemSize) {
				return true;
			}
			else
			{
				errorMessage("Please select a number between 0 and " + std::to_string(iMenuItemSize) + "\n");
			}
		}
		else
		{
			errorMessage("You have typed something which isn't recognised as a command\n");
		}
	} while (true);
}
//This wipes an entire text file blank
bool boundaryCheckValueIsValid(int iValue, int iMin, int iMax)
{
	if (iValue < iMin)
	{
		std::cout << "\nToo low! Try again!\n\n";
		return false;
	}
	if (iValue > iMax)
	{
		std::cout << "\nToo high! Try again!\n\n";
		return false;
	}
	return true;
}
bool isSingleAlphaCharacter(std::string sValue) {

	return std::find_if(sValue.begin(), sValue.end(), [](char character) {
		return !isalpha(character);
		}) == sValue.end() && sValue.size() == 1;

}
bool boundaryCheckValueIsValid(double dValue, double iMin, double iMax) {
	if (dValue < iMin)
	{
		std::cout << "\nThe number you have entered is too low! Try again!\n\n";
		return false;
	}
	if (dValue > iMax)
	{
		std::cout << "\nThe number you have entered is too high! Try again!\n\n";
		return false;
	}
	return true;
}
bool isInputANumber(std::string sLine, double* dValue) {

	for (const unsigned char& c : sLine)
	{
		if (isalpha(c) || isspace(c))
		{
			std::cout << "\n#Invalid input!\nEnter a number with no characters or spaces, and don't enter a ridiculous amount!\n\n#";
			return false;
		}
	}
	try
	{
		*dValue = stod(sLine);
	}
	catch (...)
	{
		std::cout << "\n#Invalid input!\nEnter a number with no characters or spaces, and don't enter a ridiculous amount!\n\n#";
		return false;
	}
	return true;
}
//This function takes a string through the parameter and then checks if it has either has characters or spaces
bool isInputANumber(std::string sLine, int* iValue) {

	for (const unsigned char& c : sLine)
	{
		if (isalpha(c) || isspace(c) || !isdigit(c))
		{
			std::cout << "\n#Invalid input! Enter a number with no characters or spaces.#";
			return false;
		}
	}
	//if an exception is caused with the conversion e.g. it going beyond the scope of the INT size it will catch it
	try
	{
		*iValue = stoi(sLine);
	}
	catch (...)
	{
		std::cout << "\n#Invalid input! Enter a number with no characters or spaces.#";
		return false;
	}

	return true;
}


void clearTextFileContents(std::string inputFilePath)
{
	std::ofstream ofs;
	ofs.open(inputFilePath, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}
void nothingToDisplayMessage()
{
	std::cout << "\n\t#There is currently nothing to display.\n\tPlease use option 1 in the main menu to add item(s).#\n";
}

void displayInvalidCommandMessage()
{
	std::cout << "#Invalid command, please try again.#";
}
//This function ensures that the user can't enter the character ',' due to it being used as a delimiter when saving and loading files
bool isStringCharacterAllowed(std::string sValue)
{
	for (const char& c : sValue)
	{
		if (c == ',')
		{
			std::cout << "\n',' is not allowed.\n";
			std::cout << "Please enter valid characters only!\n";
			return false;
		}
	}
	return true;
}
//This is used for sentencing one of my sentences for the procedure "Display_Warning()", 
//if more than one item underperformed it will display "products" 
//as in plural, and if only one item underperformed (less than 5% of total sales) 
//then "product" as in singular will be displayed.
std::string productOrProducts(int iNumber)
{
	return (iNumber > 1) ? "products" : "product";
}
//This clears the std::cin buffer if an error is detected after the std:: failed
void performInvalidOperation() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\n";
	displayInvalidCommandMessage();
}

//These are overloaded functions to display a message as well input into the console
void messageAndInput(std::string prompt, std::string* value)
{
	std::cout << "  " << prompt;
	std::getline(std::cin >> std::ws, *value);


}
void messageAndInput(std::string prompt, std::size_t* iIndex)
{
	std::cout << "  " << prompt;
	std::cin >> *iIndex;

}
//These are overloaded functions to display a message as well input into the console
void messageAndInput(std::string prompt, const std::size_t iIndex, std::string* value)
{
	std::cout << prompt;
	std::cout << char(iIndex);
	std::getline(std::cin >> std::ws, *value);
}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "int"
void messageAndInput(std::string prompt, int* value)
{
	std::cout << prompt;
	std::cin >> *value;
}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "double"
void messageAndInput(std::string prompt, double* value)
{
	std::cout << prompt;
	std::cout << char(156);
	std::cin >> *value;

}
//Overloaded function which displays a message of whatever is passed in and an input of datatype "char"
void messageAndInput(std::string prompt, unsigned char* value) {
	std::cout << prompt;
	std::cin >> *value;
}

bool isInputValid() //This checks whether the std:cin is valid
{
	bool bError = false;
	if (!std::cin)
	{
		performInvalidOperation();
		bError = true;
	}
	else
	{
		bError = false;
	}
	return bError;
}

void message(std::string sMessage) {
	std::cout << "  " << sMessage;
}
void successMessage(std::string sMessage) {
	std::cout << "  (Success) " + sMessage;
}
void warningMessage(std::string sMessage) {
	std::cout << "  (Warning) " + sMessage;
}
void errorMessage(std::string sMessage) {
	std::cout << "  (ERROR) " + sMessage;
}
bool isStringLengthValid(std::string sString, const std::size_t stLengthMinimum, const std::size_t stLengthMaximum)
{
	if (sString.size() < stLengthMinimum)
	{

		std::cout << "\n\t#The item name you're trying to enter is too short!\n\tTry again!\n";
		return false;
	}
	else if (sString.size() > stLengthMaximum)
	{
		std::cout << "\n\t#The item name you're trying to enter is too long!\n\tTry again!\n";
		return false;
	}
	else
	{
		return true;
	}

}
