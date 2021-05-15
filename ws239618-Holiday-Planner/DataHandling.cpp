#include "DataHandling.h"

bool checkIfUsernameIsUnique(std::vector<clsUser>&vUsers, std::string sUsername) {
    for (clsUser& objUser : vUsers) {
        if (objUser.get_username() == sUsername) {
            return false;
        }
    }
    return true;
}
void createAnAccount(std::vector<clsUser>& vUsers) {

    std::string sUsername = "";
    std::string sPassword = "";
    std::string sConfirmPassword = "";
    bool uniqueUsername = false;
    confirmYesOrNo("Are you sure you want to create a new account? (y/n): ");
    do 
    {
        messageAndInput("Enter a unique username: ", &sUsername);
        uniqueUsername = checkIfUsernameIsUnique(vUsers, sUsername);
        if (uniqueUsername == false) {
            message("This username isn't unique, please try another one!\n");
        }
    } 
    while (uniqueUsername == false);
   
    messageAndInput("Enter a new password: ", &sPassword);;;;;;;
    messageAndInput("Re-enter new password: ", &sConfirmPassword);

}
void startHolidayProgram(std::string sUserReportsCSV, std::vector<clsUser>& vUsers, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage) {

    int iOption = 0;
    std::string sOption = "";
    int iErrorCode = 0;
    std::shared_ptr<clsUser>objUser;
    clsHolidayBreakdown objTrip;
    do
    {
        std::string sUsername = "";
        std::string sPassword = "";
        displayLoginError(iErrorCode);
        message("Guess login credentials are: \n");
        message("Username: user\n");
        message("Password: 123\n");
        //MENU
        message("LOGIN MENU\n\n");
        message("1. Login with an already exisiting account\n");

        message("0. Exit program completely\n\n");
        //OPTIONS
        if (enterInteger("Enter choice: ", sOption, iOption, 2))
        {

            switch (iOption)
            {
            case 0:
            {
                return;
            }
            case 1:
                //Assigning the variable which holds the ::iterator of the end of objUsers vector, it will remain the end if they user enters incorrect login details
                if (login(vUsers, objTrip, objUser))
                {
                    system("cls");
                    mainMenu(vAllHolidays, objTrip, sUserReportsCSV, "users.csv", vUsers, dVAT, dDiscountPercentage);
                }
                else
                {
                    system("cls");
                    iErrorCode = 1;
                }
                break;
            
            }
        }
    } while (true);
}
void loadHolidaysFromCSV(std::string sHolidayCSV, std::vector<clsHoliday>& vAllHolidays) {
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file(sHolidayCSV);
    while (getline(file, sLine))
    {
        std::stringstream ssSplit(sLine);
        objSplit.resize(0);

        while (getline(ssSplit, sResult, ','))
        {
            objSplit.push_back(sResult);
        }
        if (objSplit.size() != 0)
        {
            vAllHolidays.push_back(clsHoliday{ stoi(objSplit.at(0)), objSplit.at(1), stod(objSplit.at(2)), stoi(objSplit.at(3)) });
        }
    }
}

std::vector<clsHoliday>::iterator findHoliday(int iHolidayID, std::vector<clsHoliday>& vAllHolidays)
{
    return std::find_if(vAllHolidays.begin(), vAllHolidays.end(), [&](clsHoliday& objHoliday) {
        return objHoliday.getId() == iHolidayID;
        });
}
clsHoliday findHolidayByName(std::string sHolidayName, std::vector<clsHoliday>& vAllHolidays) {
    return *std::find_if(vAllHolidays.begin(), vAllHolidays.end(), [&](clsHoliday& objHoliday) {
        return objHoliday.getName() == sHolidayName;
        });
}

void loadActivitiesFromCSV(std::string sActivitiesCSV, std::vector<clsHoliday>& vAllHolidays) {
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file(sActivitiesCSV);
    while (getline(file, sLine))
    {
        std::stringstream ssSplit(sLine);
        objSplit.resize(0);

        while (getline(ssSplit, sResult, ','))
        {
            objSplit.push_back(sResult);
        }
        if (objSplit.size() != 0)
        {
            int iHolidayID = stoi(objSplit.at(3));
            findHoliday(iHolidayID, vAllHolidays)->addActivity(clsActivity{ stoi(objSplit.at(0)), objSplit.at(1), stod(objSplit.at(2)), stoi(objSplit.at(3)), objSplit.at(4) });
        }
    }
}
void addNewLocationToCSV(clsHoliday& objLocation, std::vector<clsHoliday>& vAllHolidays)
{
    vAllHolidays.push_back(objLocation);
}
/* void clsPackageHolidaySystem::add_custom_activity(clsTrip& objTrip) {
     std::string sActivityName;
     double dEstimatedCost = 0;
     std::cout << "Enter custom activity's name: ";
     std::cin >> sActivityName;
     std::cout << "Enter estimated cost: ";
     std::cin >> dEstimatedCost;
     objTrip.set_custom_activity(clsActivity{sActivityName, dEstimatedCost});
 }*/

std::vector<clsUser>::iterator findUser(std::vector<clsUser>& objUsers, std::string sUsername) {
    return std::find_if(objUsers.begin(), objUsers.end(), [&](auto& user) {return user.get_username() == sUsername; });
}

bool areAnyHolidaysAvailable(int iFamilySize, std::vector<clsHoliday>& vAllHolidays) {
    for (clsHoliday& objHoliday : vAllHolidays)
    {
        if (objHoliday.isHolidayAvailableForFamily(iFamilySize))
        {
            return true;
        }
    }
    return false;
}

void displayHolidayMenu(const clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays) {
    int iCount = 1;
    const int nameWidth = 22;
    message("CHOOSE A HOLIDAY LOCATION!\n\n");
    printElement("", 9);
    printElement("LOCATION ", nameWidth);
    printElement("COST PER PERSON ", nameWidth);
    printElement("MINIMUM TRAVELLERS ", nameWidth);
    printElement("Is family eligible? ", nameWidth);
    std::cout << "\n";
    for (auto& objHoliday : vAllHolidays) {

        printElement("   " + std::to_string(iCount++) + ". ", 9);
        printElement(objHoliday.getName(), nameWidth);
        printElement(char(156) + toStringWithPrecision(objHoliday.getCostPerPerson(), 2), nameWidth);
        printElement(std::to_string(objHoliday.getMinimumTravellers()), nameWidth);

        if (objHoliday.isHolidayAvailableForFamily(objTrip.getUser()->familySize())) {
            printElement("Yes", nameWidth);
        }
        else {
            printElement("No", nameWidth);
        }
        std::cout << "\n";
    }
}
void chooseHolidayErrorMessage(int& iErrorCode, std::string sHolidayName) {
    if (iErrorCode != 0) {
        switch (iErrorCode) {
        case 1: {
            message("\n  Sadly, you are not eligible for the holiday " + sHolidayName + ".\n");
            iErrorCode = 0;
            break;
        }
        }
    }
}
bool chooseHoliday(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays)
{
    int iPartySize = 0;
    std::string sOption = "";
    int iOption = 0;
    std::string sHolidayName = "";
    int iErrorCode = 0;
    do
    {
        chooseHolidayErrorMessage(iErrorCode, sHolidayName);
        displayHolidayMenu(objTrip, vAllHolidays);

        if (areAnyHolidaysAvailable(objTrip.getUser()->familySize(), vAllHolidays))
        {
            if (enterInteger("\n  Press 0 to go back or enter a number from the menu (e.g. 1): ", sOption, iOption, (int)vAllHolidays.size()))
            {
                if (iOption == 0) {

                    system("cls");
                    return false;
                }
                if (vAllHolidays.at(static_cast<std::size_t>(iOption) - 1).isHolidayAvailableForFamily(objTrip.getUser()->familySize()))
                {
                    objTrip.setChosenHoliday(&vAllHolidays.at(static_cast<std::size_t>(iOption) - 1));
                    return true;
                }
                else
                {
                    sHolidayName = vAllHolidays.at(static_cast<std::size_t>(iOption - 1)).getName();
                    iErrorCode = 1;
                    system("cls");
                }
            }
        }
        else
        {
            message("\n  Sadly, you are not eligible for any of our holidays, as your family size does not meet any of our holiday's criteria.\n");
            return false;
        }
    } while (true);



}
bool hasUserChosenActivity(clsHolidayBreakdown& objTrip, std::string sActivityName) {
    for (clsActivity* objActivity : objTrip.getChosenActivities()) {
        if (objActivity->getName() == sActivityName) {
            return true;
        }
    }
    return false;
}
void displayActivityMenu(clsHolidayBreakdown& objTrip) {
    const int nameWidth = 18;
    int iCount = 1;
    int iStandardActivitiesSize = (int)objTrip.getChosenHoliday()->m_objActivities.size();
    int iCustomActivitiesSize = (int)objTrip.getChosenHoliday()->m_objCustomActivities.size();
    message("  ADD ACTIVITY\n\n");
    printElement(" ", 9);
    printElement("ACTIVITY ", nameWidth);
    printElement("COST ", nameWidth);
    printElement("TYPE", nameWidth);
    printElement("ADDED?", nameWidth);
    std::cout << "\n";
    for (clsActivity* objActivity : objTrip.getChosenHoliday()->m_objStandardAndCustomActivities)
    {
        printElement("  " + std::to_string(iCount++) + ". ", 9);
        printElement(objActivity->getName(), nameWidth);
        printElement(char(156) + toStringWithPrecision(objActivity->getCostPerPerson(), 2), nameWidth);
        printElement(objActivity->getActivityType(), nameWidth);
        if (hasUserChosenActivity(objTrip, objActivity->getName()))
        {
            printElement("Yes", nameWidth);
        }
        else {
            printElement("No", nameWidth);
        }

        std::cout << "\n";
    }
    /*
    for (clsCustomActivity objCustomActivity : objTrip.getChosenHoliday()->m_objCustomActivities) {
        printElement("  " + std::to_string(iCount++) + ". ", 9);
        printElement(objCustomActivity.getName(), nameWidth);
        printElement(char(156) + toStringWithPrecision(objCustomActivity.getCostPerPerson(), 2), nameWidth);
        printElement(objCustomActivity.getActivityType(), nameWidth);
        if (hasUserChosenActivity(objTrip, objCustomActivity.getName()))
        {
            printElement("Yes", nameWidth);
        }
        else {
            printElement("No", nameWidth);
        }
    }
    */

    std::cout << "\n";
    printElement("  " + std::to_string(iStandardActivitiesSize + iCustomActivitiesSize + 1) + ". Add your own activity\n", nameWidth);
}

void activitySuccessMessage(int iActivityErrorCode, std::string sActivityName, double dTotalCost) {
    if (iActivityErrorCode != 0) {
        switch (iActivityErrorCode)
        {
        case 1:
        {
            std::cout << "\n";
            successMessage("You have added " + sActivityName + " to your plan.\n  Total activity cost for family: " + char(156) + toStringWithPrecision(dTotalCost, 2) + "\n");
            iActivityErrorCode = 0;
            break;
        }
        case 2:
        {
            std::cout << "\n";
            successMessage("You have removed " + sActivityName + " from your holiday plan\n");
            iActivityErrorCode = 0;
            break;
        }
        case 3:
        {
            std::cout << "\n";
            successMessage("You have chosen not to remove " + sActivityName + " from your holiday plan\n");
            iActivityErrorCode = 0;
            break;
        }
        }
    }
}



void addCustomActivity(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays)
{
    std::string sNameOfActivity = "";
    std::string sCostPerPerson = "";
    double dCostPerPerson = 0;
    int iHolidayID = objTrip.getChosenHoliday()->getId();
    int iNewCustomActivityID = objTrip.getChosenHoliday()->setUniqueIDForActivity();
    std::string sUsername = objTrip.getUser()->get_username();
    messageAndInput("Enter name of activity: ", &sNameOfActivity);
    if (enterDouble("Enter cost per person: ", sCostPerPerson, dCostPerPerson))
    {
        clsCustomActivity objNewCustomActivity(objTrip.getChosenHoliday()->setUniqueIDForActivity(), sNameOfActivity, dCostPerPerson, iHolidayID, "Custom", sUsername);
        objTrip.getChosenHoliday()->addCustomActivity(objNewCustomActivity);
        //objTrip.setActiveUserCustomActivities(vAllHolidays);
        AppendCustomActivityToTextFile(objTrip, objNewCustomActivity);
        objTrip.loadAllCustomActivities("customActivities.csv");
        objTrip.setActiveUserCustomActivities(vAllHolidays);
        //saveCustomActivity(vAllHolidays);
    }
}
void AppendCustomActivityToTextFile(clsHolidayBreakdown& objTrip, clsCustomActivity objNewCustomActivity)
{
    std::ofstream file;
    file.open("customActivities.csv", std::ios_base::app);
    file << objNewCustomActivity.getId() << "," << objNewCustomActivity.getName() << "," << objNewCustomActivity.getCostPerPerson() << "," << objNewCustomActivity.getLocationId() << "," << objNewCustomActivity.getActivityType() << "," << objNewCustomActivity.getUsername() << ",\n";
    file.close();
}
void chooseActivity(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays) {

    std::string sOption = "";
    int iOption = 0;
    int iActivitySuccessCode = 0;
    std::string sSelectedHolidayName = "";
    double dTotalCost = 0;
    std::cout << "\n";
    int iStandardAndCustomActivitiesSize = 0;
    do
    {
        objTrip.loadAllCustomActivities("customActivities.csv");
        objTrip.setActiveUserCustomActivities(vAllHolidays);
        objTrip.getChosenHoliday()->setStandardAndCustomActivities();
        iStandardAndCustomActivitiesSize = (int)objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.size();
        system("cls");
        displayActivityMenu(objTrip);
        activitySuccessMessage(iActivitySuccessCode, sSelectedHolidayName, dTotalCost);

        if (enterInteger("\n  Press 0 to exit or choose an activity: ", sOption, iOption, iStandardAndCustomActivitiesSize + 1))
        {
            if (iOption == iStandardAndCustomActivitiesSize + 1)
            {
                addCustomActivity(objTrip, vAllHolidays);

            }
            else if (iOption == 0)
            {
                system("cls");
                return;
            }
            else
            {
                if (!hasUserChosenActivity(objTrip, objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1)->getName()))
                {
                    sSelectedHolidayName = objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1)->getName();
                    dTotalCost = objTrip.totalActivityCost(iOption - 1);
                    objTrip.addChosenActivity(objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1));
                    iActivitySuccessCode = 1;
                }
                else
                {
                    warningMessage("It looks like you've already selected this activity\n");
                    if (confirmYesOrNo("Do you wish to remove this activity? (y/n): "))
                    {
                        sSelectedHolidayName = objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1)->getName();
                        objTrip.removeChosenActivityByID(objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1)->getId());
                        iActivitySuccessCode = 2;
                    }
                    else
                    {
                        sSelectedHolidayName = objTrip.getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption - 1)->getName();
                        iActivitySuccessCode = 3;
                    }
                }
            }
        }
    } while (true);
}
std::vector<clsHoliday>::iterator find_location_by_id(int iLocationID, std::vector<clsHoliday>& vAllHolidays)
{
    return std::find_if(vAllHolidays.begin(), vAllHolidays.end(), [&](auto& objLocation) {return objLocation.getId() == iLocationID; });
}

double totalPrice(clsHolidayBreakdown& objTrip)
{
    int iFamilySize = objTrip.getUser()->familySize();
    return (objTrip.getChosenHoliday()->getCostPerPerson() * iFamilySize) + (objTrip.getChosenHoliday()->getCostPerPerson() * iFamilySize);
}

double VAT(clsHolidayBreakdown& objTrip, double dVAT) {

    return dVAT * totalPrice(objTrip);
}

double discount(clsHolidayBreakdown& objTrip, double dDiscountPercentage)
{
    const int iAdultsCriteria = 2;
    const int iChildrenCriteria = 2;
    double dTotalPrice = totalPrice(objTrip);

    if (objTrip.getUser()->getChildCount() >= iChildrenCriteria && objTrip.getUser()->getAdultCount() >= iAdultsCriteria)
    {
        return dTotalPrice * dDiscountPercentage;
    }
    else
    {
        return 0;
    }
}
void updateUsersCSV(std::vector<clsUser>& objUsers, std::string usersCSV)
{

    std::ofstream file;
    file.open(usersCSV);
    for (clsUser& objUser : objUsers)
    {
        file << objUser.get_name() << "," << objUser.get_username() << "," << objUser.get_password() << "," << objUser.getAdultCount() << "," << objUser.getChildCount() << ",\n";
    }
    file.close();
}

bool isUsernameUnique(std::vector<clsUser>& objUsers, std::string sUsername) {
    return std::find_if(objUsers.begin(), objUsers.end(), [&](auto& objUser) {
        return objUser.get_username() == sUsername;
        }) == objUsers.end();
}
void create_account(std::vector<clsUser>& objUsers) {
    std::string sName, sUsername = "", sPassword = "", sAge = "", sNumberOfAdultsInFamily = "", sNumberOfChildrenInFamily = "";
    int iAge = 0;
    int iNumberOfAdultsInFamily = 0;
    int iNumberOfChildrenInFamily = 0;
    messageAndInput("What's your full name?: ", &sName);

    if (enterInteger("What's your age?: ", sAge, iAge, 100)) {
        do
        {
            clsUser objNewUser;
            messageAndInput("Enter a unqiue username: ", &sUsername);
            if (isUsernameUnique(objUsers, sUsername))
            {
                messageAndInput("Enter a secure password: ", &sPassword);
                if (enterInteger("How many adults are in your party?: ", sNumberOfAdultsInFamily, iNumberOfAdultsInFamily, 10))
                {
                    objNewUser.setAdultCount(iNumberOfAdultsInFamily);
                }
                if (enterInteger("How many children are in your party?:", sNumberOfChildrenInFamily, iNumberOfChildrenInFamily, 10))
                {
                    objNewUser.setChildCount(iNumberOfChildrenInFamily);
                }
                objUsers.push_back(objNewUser);
                message("You have successfully created a new account\n");
            }
            else
            {
                message("The username you have tried already exists\n");
            }
        } while (true);
    }
}

std::shared_ptr<clsUser>check_credentials(std::vector<clsUser>& objUsers, std::string sUsername, std::string sPassword) {

    for (auto& objUser : objUsers) 
    {
        if (objUser.get_username() == sUsername && objUser.get_password() == sPassword)
        {
            return std::make_shared<clsUser>(objUser);
        }
    }
}
bool login(std::vector<clsUser>& objUsers, clsHolidayBreakdown& objTrip, std::shared_ptr<clsUser>& objPassedUser) {
    std::string sUsername, sPassword = "";
    messageAndInput("Enter your username: ", &sUsername);
    messageAndInput("Enter your password: ", &sPassword);
    auto objUser = check_credentials(objUsers, sUsername, sPassword);
    if (objUser != nullptr)
    {
        objPassedUser = objUser;
        objTrip.setUser(objPassedUser);
        return true;
    }
    else {
        return false;
    }
}
void userSystemSuccessMessage(int& iSuccessMessageCode) {
    if (iSuccessMessageCode != 0)
    {
        switch (iSuccessMessageCode) {
        case 1: {
            message("[SUCCESS] Your family details has been updated\n\n");
            iSuccessMessageCode = 0;
            break;
        } case 2: {
            message("You made no updates to your family information\n\n");
        }
        }
    }
}
void holidayExpenditureSuccessMessage(int& iSuccessMessageCode) {
    if (iSuccessMessageCode != 0)
    {
        switch (iSuccessMessageCode)
        {
        case 1:
        {
            successMessage("You have successfully saved this holiday plan.\n");
            break;
        }
        }

    }
}
void saveCustomActivity(std::vector<clsHoliday>& vAllHolidays) {
    //updating all information regarding selected activities in the in the CSV
    std::ofstream file;
    file.open("customActivities.csv");
    for (auto& objHoliday : vAllHolidays) {
        for (auto& objActivity : objHoliday.m_objCustomActivities) {
            file << objActivity.getId() << "," << objActivity.getName() << "," << objActivity.getCostPerPerson() << "," << objActivity.getLocationId() << "," << objActivity.getActivityType() << "," << objActivity.getUsername() << ",\n";
        }
    }
    file.close();
}
void holidayExpenditureReport(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage, std::string reportsCSV) {
    system("cls");
    message("\n  " + toStringWithPrecision(objTrip.getChosenHoliday()->getName()) + " EXPENDITURE REPORT \n");
    //message("You have chosen the activity: " + objTrip.getChosenActivities().at(0).get_name() + "\n");
    message("Total price of trip: " + static_cast<std::string>(char(156) + toStringWithPrecision(totalPrice(objTrip), 2) + "\n"));
    message(toStringWithPrecision((dVAT * 100), 0) + "% VAT: " + toStringWithPrecision(VAT(objTrip, dVAT), 2) + "\n");
    objTrip.displayChosenActivities();
    message("Total price + VAT is " + toStringWithPrecision((totalPrice(objTrip) + VAT(objTrip, dVAT)), 2) + "\n");
    message("Discount: " + toStringWithPrecision(discount(objTrip, dDiscountPercentage), 2) + "\n");
    std::string sAnswer = "";

    if (confirmYesOrNo("Do you wish to save this report? (y/n): "))
    {
        if (!objTrip.doesHolidayPlanExist(objTrip.getChosenHoliday()->getName()))
        {

            clsReport objR(objTrip.getUser()->get_username(), objTrip.getChosenHoliday()->getName(), totalPrice(objTrip), VAT(objTrip, dVAT), discount(objTrip, dDiscountPercentage), objTrip.getUser()->getAdultCount(), objTrip.getUser()->getChildCount());
            objR.setAddedActivities(objTrip.getChosenActivities());

            objTrip.addReport(objR, reportsCSV);
        }
        else
        {
            if (confirmYesOrNo("\n  (WARNING) It appears the holiday you're trying to save already exists.\n  Do wish to update your " + objTrip.getChosenHoliday()->getName() + " plan? (y/n): "))
            {
                clsReport objR(objTrip.getChosenActivities(), objTrip.getUser()->get_username(), objTrip.getChosenHoliday()->getName(), totalPrice(objTrip), VAT(objTrip, dVAT), discount(objTrip, dDiscountPercentage), objTrip.getUser()->getAdultCount(), objTrip.getUser()->getChildCount());
                if (objTrip.updateHolidayPlanReport(objTrip.getChosenHoliday()->getName(), objR, reportsCSV)) {
                    successMessage("You have updated your " + objTrip.getChosenHoliday()->getName() + "\n");

                }
            }
        }

        system("cls");
    }
    else
    {
        system("cls");
    }
}
double totalActivityCost(std::vector<clsActivity*>& vActivities, int iFamilySize) {
    double dSum = 0;
    for (auto& objActivity : vActivities) {
        dSum += objActivity->getCostPerPerson() * iFamilySize;
    }
    return dSum;
}
void displayChosenActivities(std::vector<clsActivity*>& vActivities, int iFamilySize, std::string sHolidayName)
{
    int iCount = 1;
    if (vActivities.size() != 0)
    {
        for (auto& objActivity : vActivities)
        {
            std::string sActivityName = objActivity->getName();
            message("\n  ACTIVITY " + std::to_string(iCount++) + "\n");
            message("Name: " + sActivityName + "\n");
            message("Cost per person: " + static_cast<std::string>(char(156) + toStringWithPrecision(objActivity->getCostPerPerson(), 2) + "\n"));
            message("Total " + sActivityName + " cost for family: "
                + char(156) + toStringWithPrecision((objActivity->getCostPerPerson() * iFamilySize), 2) + "\n");

        }
        message("\n  Total activity(s) cost: " + static_cast<std::string>(char(156) + toStringWithPrecision(totalActivityCost(vActivities, iFamilySize), 2) + "\n"));
    }
    else
    {
        message("  You haven't included any activities for your " + sHolidayName + " holiday\n");
    }
}
void displaySelectedReport(clsReport&& objReport) {

    message("DISPLAYING HOLIDAY REPORT FOR " + stringToUpper(objReport.getHolidayName()) + "\n");

    message("Total Price: " + static_cast<std::string>(char(156) + toStringWithPrecision(objReport.getTotalPrice(), 2) + "\n"));
    message("20% of Total Price (VAT): " + static_cast<std::string>(char(156) + toStringWithPrecision(objReport.getVAT(), 2) + "\n"));
    displayChosenActivities(objReport.m_objAddedActivities, (objReport.getAdultCount() + objReport.getChildCount()), objReport.getHolidayName());
    message("Discount: " + static_cast<std::string>(char(156) + toStringWithPrecision(objReport.getDiscount(), 2) + "\n"));

}
void userSystemErrorMessage(int& iErrorCode) {
    if (iErrorCode != 0) {
        switch (iErrorCode)
        {
        case 1:
        {
            warningMessage("You haven't saved any reports\n\n");
            iErrorCode = 0;
        }
        }
    }
}

void planAHoliday(clsHolidayBreakdown& objTrip, std::vector<clsHoliday>& vAllHolidays, double dVAT, double dDiscountPercentage, std::string reportsCSV) {
    system("cls");
    if (chooseHoliday(objTrip, vAllHolidays))
    {
        system("cls");
        message(stringToUpper(objTrip.getChosenHoliday()->getName()) + " holiday\n");
        std::string sSubMenuItem = "";
        int iSubMenuItem = 0;
        do
        {
            message("1. Would you like to add activities to your holiday?\n");
            message("2. See holiday expenditure report\n");
            message("0. MAIN MENU\n");
            if (enterInteger("Enter an option from the menu: ", sSubMenuItem, iSubMenuItem, 2))
            {
                if (iSubMenuItem == 0)
                {
                    std::string sAnswer = "";
                    if (confirmYesOrNo("\n  (WARNING) If you haven't saved your report, your holiday plan will be lost and you will have to re-do this process.\n  Are you sure you want to go to the main menu? (y/n): "))
                    {
                        system("cls");
                        return;
                    }
                    else
                    {
                        system("cls");
                        return;
                    }
                }
                switch (iSubMenuItem)
                {
                case 1:
                {

                    system("cls");
                    objTrip.loadAllCustomActivities("customActivities.csv");
                    objTrip.setActiveUserCustomActivities(vAllHolidays);
                    objTrip.getChosenHoliday()->setStandardAndCustomActivities();
                    chooseActivity(objTrip, vAllHolidays);

                    break;
                }
                case 2:
                {
                    holidayExpenditureReport(objTrip, vAllHolidays, dVAT, dDiscountPercentage, reportsCSV);
                    break;
                }
                }
            }
        } while (true);
    }
}
void enterFamilyDetails(std::vector<clsHoliday>& vAllHolidays, clsHolidayBreakdown& objTrip, int& iSuccessMessageCode, std::vector<clsUser>& objUsers, std::string usersCSV) {

    int iChildCount = 0;
    std::string sChildCount = "";
    int iAdultCount = 0;
    std::string sAdultCount = "";
    std::string sAnswer = "";

    if (confirmYesOrNo("\n  [i] There are " + std::to_string(objTrip.getUser()->familySize()) + " members in your family.\n"
        + "  Do you wish to edit your family information? (y/n): "))
    {
        if (enterInteger("How many adults are in your party?: ", sAdultCount, iAdultCount, 10))
        {
            objTrip.getUser()->setAdultCount(iAdultCount);
            findUser(objUsers, objTrip.getUser()->get_username())->setAdultCount(iAdultCount);
        }
        if (enterInteger("How many children are in your party?:", sChildCount, iChildCount, 10))
        {
            objTrip.getUser()->setChildCount(iAdultCount);
            findUser(objUsers, objTrip.getUser()->get_username())->setChildCount(iChildCount);
            updateUsersCSV(objUsers, usersCSV);
            iSuccessMessageCode = 1;
            return;
        }
    }
    else
    {
        iSuccessMessageCode = 2;
    }
}

void savedHolidayReportsMenu(clsHolidayBreakdown& objTrip, int& iErrorCode, std::string reportsCSV, std::vector<clsHoliday>& vAllHolidays) {

    do
    {
        if (objTrip.reportSize() != 0) {
            system("cls");
            std::string sOption = "";
            int iOption = 0;
            objTrip.displayReportMenu();
            if (iErrorCode != 1)
            {
                if (enterInteger("\n  Press 0 to go back or choose a report to display: ", sOption, iOption, objTrip.reportSize()))
                {
                    if (iOption == 0) {
                        system("cls");
                        break;
                    }
                    do
                    {
                        system("cls");


                        displaySelectedReport(objTrip.selectReport((std::size_t)iOption - 1));

                        if (enterInteger("\n  Enter 0 to go back to the previous page or 1 to delete report: ", sOption, iOption, 1)) {
                            if (iOption == 0)
                            {
                                break;
                            }
                            if (iOption == 1) {


                                objTrip.deleteSavedReport(objTrip.selectReport((std::size_t)iOption - 1));
                                objTrip.saveReportCSV(reportsCSV);
                                objTrip.loadAllReportsCSV("reports.CSV");
                                objTrip.loadAllActivityData(vAllHolidays);
                                objTrip.assignSavedActivities(vAllHolidays);
                                objTrip.setActiveUserReports();
                                break;
                            }

                        }
                    } while (true);
                }
            }
        }
        else {
            iErrorCode = 1;
            system("cls");
            break;
        }

    } while (true);
}
void mainMenu(std::vector<clsHoliday>& vAllHolidays, clsHolidayBreakdown& objTrip, std::string reportsCSV, std::string usersCSV, std::vector<clsUser>& objUsers, double dVAT, double dDiscountPercentage) {
    std::string sMenuItem = "";
    int iMenuItem = 0;
    bool bExit = true;
    int iSuccessMessageCode = 0;
    int iErrorCode = 0;
    while (true)
    {
        message("[Logged in as " + objTrip.getUser()->get_name() + "]\n\n");
        userSystemSuccessMessage(iSuccessMessageCode);
        userSystemErrorMessage(iErrorCode);
        message("MAIN MENU\n\n");
        message("1. Plan a Holiday\n");
        message("2. Your Family Details\n");
        message("3. View Saved Holiday Reports\n");
        message("0. Logout\n");
        if (enterInteger("\n  Enter an option from the menu: ", sMenuItem, iMenuItem, 3)) {

            switch (iMenuItem)
            {
            case 0:
            {
                if (confirmYesOrNo("\n  Are you sure you want to logout? (y/n): "))
                {
                    //This will remove any information about the user who has logged in
                    objTrip.clearSession();
                    system("cls");
                    return;
                }
                system("cls");
                break;
            }
            case 1:
            {

                planAHoliday(objTrip, vAllHolidays, dVAT, dDiscountPercentage, reportsCSV);
                break;
            }
            case 2:
            {
                enterFamilyDetails(vAllHolidays, objTrip, iSuccessMessageCode, objUsers, usersCSV);
                system("cls");
                break;
            }
            case 3:
            {

                objTrip.loadAllCustomActivities("customActivities.csv"); //loading all custom activities into a vector by all users of the system
                objTrip.setActiveUserCustomActivities(vAllHolidays); //Will sort through all the custom activities added by users and apply them to person currently logged in

                objTrip.loadAllActivityData(vAllHolidays);
                objTrip.loadAllReportsCSV("reports.csv");
                objTrip.assignSavedActivities(vAllHolidays);
                objTrip.setActiveUserReports();

                savedHolidayReportsMenu(objTrip, iErrorCode, reportsCSV, vAllHolidays);
                break;
            }

            }
        }
    }
}

void displayAdminMenu()
{
    message("1. Add a new location\n");
    message("2. Add a new activity to location\n");
    message("3. Approve / reject activities by users\n\n");
}

void addNewHoliday() {
    std::string sLocationName;
    double dCostPerPerson;
    int iMinimumTravellers;
    messageAndInput("Enter name of new location: ", &sLocationName);
    messageAndInput("Enter cost per person: ", &dCostPerPerson);
    messageAndInput("Enter minimum travellers: ", &iMinimumTravellers);
}
//void start_admin_system(clsPackageHolidaySystem& objSystem) {
//    int iOption = 0;
//    std::string sOption = "";
//    do {
//        display_admin_menu();
//        if (enterInteger("Enter an option from the menu: ", sOption, iOption, 3)) {
//        }
//    } while (true);
//}
void loadUsersFromCSV(std::string sUserCSV, std::vector<clsUser>* vUsers) {
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file(sUserCSV);
    while (getline(file, sLine))
    {
        std::stringstream ssSplit(sLine);
        objSplit.resize(0);

        while (getline(ssSplit, sResult, ','))
        {
            objSplit.push_back(sResult);
        }
        if (objSplit.size() != 0)
        {
            vUsers->push_back(clsUser{ objSplit.at(0),objSplit.at(1), objSplit.at(2), stoi(objSplit.at(3)), stoi(objSplit.at(4)) });
        }
    }
}

void displayLoginError(int& iErrorCode)
{
    switch (iErrorCode)
    {
    case 1:
    {
        errorMessage("Sorry, couldn't log you in with the credentials you provided :(\n\n");
        iErrorCode = 0;
        break;
    }
    }
}