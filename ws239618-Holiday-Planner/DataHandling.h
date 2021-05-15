#pragma once
#include <string>
#include <vector>
#include "Holiday.h"
#include "User.h"
#include <cstdlib>
#include "HolidayBreakdown.h"
//Because there is a circular dependency I need to declare clsHolidayBreakdown as a prototype
class clsHolidayBreakdown;
void AppendCustomActivityToTextFile(clsHolidayBreakdown& objTrip, clsCustomActivity objNewCustomActivity);
//This is where the user chooses an activity(s)
void chooseActivity(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays);
void addCustomActivity(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays);
void startHolidayProgram(std::string sUserReportsCSV, std::vector<clsUser>& vUsers, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage);
//Loads holidays from CSV file and stores them in a vector called "vAllHolidays"
void loadHolidaysFromCSV(std::string sHolidayCSV, std::vector<clsHoliday>& vAllHolidays);
std::vector<clsHoliday>::iterator findHoliday(int iHolidayID, std::vector<clsHoliday>& vAllHolidays);
//searches a vector of holidays by a holiday name
clsHoliday findHolidayByName(std::string sHolidayName, std::vector<clsHoliday>& vAllHolidays);

//Loads all activities and adds them to the corresponding holidays by holidayID
void loadActivitiesFromCSV(std::string sActivitiesCSV, std::vector<clsHoliday>& vAllHolidays);
//Adds new holiday to vector of holidays
void addNewLocationToCSV(clsHoliday& objLocation, std::vector<clsHoliday>& vAllHolidays);
/* void clsPackageHolidaySystem::add_custom_activity(clsTrip& objTrip) {
     std::string sActivityName;
     double dEstimatedCost = 0;
     std::cout << "Enter custom activity's name: ";
     std::cin >> sActivityName;
     std::cout << "Enter estimated cost: ";
     std::cin >> dEstimatedCost;
     objTrip.set_custom_activity(clsActivity{sActivityName, dEstimatedCost});
 }*/
 //displays saved reports by user menu
void savedHolidayReportsMenu(clsHolidayBreakdown& objTrip, int& iErrorCode, std::string reportsCSV, std::vector<clsHoliday>& vAllHolidays);
//finds a user in the vector of users
std::vector<clsUser>::iterator findUser(std::vector<clsUser>& objUsers, std::string sUsername);
//checks if any of the holidays are available based on criteria of family size
bool areAnyHolidaysAvailable(int iFamilySize, std::vector<clsHoliday>& vAllHolidays);
//Displays error messages corresponding to the chooseHoliday menu
void chooseHolidayErrorMessage(int& iErrorCode, std::string sHolidayName);
//This is where the user chooses their holiday
bool chooseHoliday(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays);
//checks if a user has chosen an activity
bool hasUserChosenActivity(clsHolidayBreakdown& objTrip, std::string sActivityName);
//displays activity menu corresponding to what holiday the user has selected.
void displayActivityMenu(clsHolidayBreakdown& objTrip);
//Displays success message of what the user has done in the activity menu
void activitySuccessMessage(int iActivityErrorCode, std::string sActivityName, double dTotalCost);
void saveCustomActivity(std::vector<clsHoliday>& vAllHolidays);
//this finds a holiday by ID
std::vector<clsHoliday>::iterator find_location_by_id(int iLocationID, std::vector<clsHoliday>& vAllHolidays);
//This calculates total price of holiday
double totalPrice(clsHolidayBreakdown& objTrip);
//This calculates VAT of total price
double VAT(clsHolidayBreakdown& objTrip, double dVAT);
//This calculates discount (if the user meets the criteria
double discount(clsHolidayBreakdown& objTrip, double dDiscountPercentage);
//This updates the CSV file if a change is made to a user, such as a family size
void updateUsersCSV(std::vector<clsUser>& objUsers, std::string usersCSV);
//This ensures a username is unique
bool isUsernameUnique(std::vector<clsUser>& objUsers, std::string sUsername);
//This creates an account for a new user
void createAccount(std::vector<clsUser>& objUsers);
//This returns a shared pointer to a user in the system
std::shared_ptr<clsUser> checkCredentials(std::vector<clsUser>& objUsers, std::string sUsername, std::string sPassword);
//this returns a shared pointer to a user in the system, where subsequently will set the session user
bool login(std::vector<clsUser>& objUsers, clsHolidayBreakdown& objTrip, std::shared_ptr<clsUser>& objPassedUser);
//This displays a success message to the main menu
void userSystemSuccessMessage(int& iSuccessMessageCode);
//This displays success messages of holiday expenditure
void holidayExpenditureSuccessMessage(int& iSuccessMessageCode);
//This displays the report of the holiday and activities the user has selected, where they are also able to save it into their saved reports place
void holidayExpenditureReport(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage, std::string reportsCSV);
//This will display the report the user selects
void displaySelectedReport(clsReport&& objReport);
//This will display error messages based on the code passed in
void userSystemErrorMessage(int& iErrorCode);
//This launches the main holiday system where user can select a holiday
void planAHoliday(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage, std::string reportsCSV);
//This allows a user to edit family details
void enterFamilyDetails(std::vector<clsHoliday>& vAllHolidays, clsHolidayBreakdown& objTrip, int& iSuccessMessageCode, std::vector<clsUser>& objUsers, std::string usersCSV);
//This is the main menu, what the user sees when they log in
void mainMenu(std::vector<clsHoliday>& vAllHolidays, clsHolidayBreakdown& objTrip, std::string reportsCSV, std::string usersCSV, std::vector<clsUser>& objUsers, double dVAT, double dDiscountPercentage);
void displayAdminMenu();

void addNewHoliday();
//loads all users from a CSV file and puts them in a vector of type "clsUser"
void loadUsersFromCSV(std::string sUserCSV, std::vector<clsUser>* vUsers);
//Dipslays login error based on what user passes in.
void displayLoginError(int& iErrorCode);
//Calculates total activity cost
double totalActivityCost(std::vector<clsActivity>& vActivities, int iFamilySize);

