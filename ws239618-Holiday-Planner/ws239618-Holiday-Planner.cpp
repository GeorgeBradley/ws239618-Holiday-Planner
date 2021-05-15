
#include "DataHandling.h"
int main()
{
    //declaring filename variables which will be used to handle about users, holidays, holiday reports etc.
    const std::string sHolidaysCSVFileName = "holidays.csv";
    const std::string sActivitiesCSVFileName = "activities.csv";
    const std::string sUsersCSVFileName = "users.csv";
    const std::string sUserReportsCSV = "reports.csv";
    //Declaring VAT and Discount Percentage rate variables, will be used when calculating the holiday report
    const double dVAT = 0.20;
    const double dDiscountPercentage = 0.10;

    //This is what will store all the session information about the user
    clsHolidayBreakdown objTrip;

    //This stores all users of the system
    std::vector<clsUser>vUsers(0);
    //This stores all holidays of the system which the user can select
    std::vector<clsHoliday>vAllHolidays(0);

    //loads all CSV files for the system
    loadHolidaysFromCSV(sHolidaysCSVFileName, vAllHolidays);
    loadActivitiesFromCSV(sActivitiesCSVFileName, vAllHolidays);
    loadUsersFromCSV(sUsersCSVFileName, &vUsers);

    //Starts main program.

    startHolidayProgram(sUserReportsCSV, vUsers, vAllHolidays, dVAT, dDiscountPercentage);

}
