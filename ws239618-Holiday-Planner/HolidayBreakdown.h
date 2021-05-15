#pragma once

#include "HolidayReport.h"
#include "myOwnFunctions.h"
#include "DataHandling.h"

struct clsActivityData
{
    std::string sUserName;
    std::string sLocationName;
    int iActivityID;
    std::string sActivityType;
};
class clsHolidayBreakdown
{
private:
    //I have decided to use a pointer here because whatever holiday the user choices will then subsequently point to a new holiday which is in the holidays vector
    clsHoliday* m_objChosenHoliday;
    std::vector<clsActivity*> m_objChosenActivities;
    std::shared_ptr<clsUser> m_objUser;
    std::vector<clsReport> m_objAllReports;
    std::vector<clsReport>m_objUserReports;
    //This is to get all added activities from all users, then will sort them out and put them into the correct report via the user ID linked with the record.
    std::vector<clsActivityData>allActivityData;
public:
    ~clsHolidayBreakdown() {

    }
    std::vector<clsCustomActivity>vAllCustomActivitiesByUsers;
    void setActiveUserCustomActivities(std::vector<clsHoliday>& vHolidays);
    void loadAllCustomActivities(std::string sCustomActivitiesCSV);
    //stores chosen activities by the user
    std::vector<clsActivity*> getChosenActivities();
    //deletes a saved report by the user
    void deleteSavedReport(clsReport objReport);
    //finds a saved report by holiday name, used when merging all information from CSV
    auto findSavedReportByHolidayName(std::string);
    //clears the session after the user logs out
    void clearSession();
    //Updates holiay plan report if the user changes a report on a holiday they've previously selected
    bool updateHolidayPlanReport(std::string sHolidayName, clsReport objUpdatedReport, std::string holidayReportsCSV);
    //Checks to see if holiday plan already exists as a report
    bool doesHolidayPlanExist(std::string sHolidayName);
    //Assings saved activities by the user 
    void assignSavedActivities(std::vector<clsHoliday>& vAllHolidays);
    //Adds report if the user hasn't already got a report selected.
    void addReport(clsReport objReport, std::string reportsCSV);
    //returns the report size
    int reportSize();
    //Returns the selected report which is used to select a report in the menu
    clsReport selectReport(int iIndex);
    //Set active user's reports
    void setActiveUserReports();
    //Displays report menu
    void displayReportMenu();
    //this saves the CSV report if changes are made
    void saveReportCSV(std::string holidayReportsCSV);
    //This loads all the information about what the user has selected as part of their holiday
    void loadAllActivityData(std::vector<clsHoliday>& vAllHolidays);
    //This loads all the reports of the users
    void loadAllReportsCSV(std::string holidayReports);
    //This calculates the total activity cost
    double totalActivityCost(int iOption);
    //This is a no argument constructor
    clsHolidayBreakdown() : m_objChosenHoliday(nullptr), m_objUser(nullptr)
    {
    }
    //This caluates the total activity cost
    double totalActivityCost();
    //This returns a shared_ptr, to subsequently set the session of the user
    std::shared_ptr<clsUser> getUser() const;
    //This displays the chosen activities of the user
    void displayChosenActivities();
    //This returns a pointer to the holiday which the user selects
    clsHoliday* getChosenHoliday() const;
    //This is a multiple argument constructor
    clsHolidayBreakdown(clsHoliday* objChosenHoliday, clsUser* objUser, std::vector<clsActivity*> objChosenActivities)
        :m_objChosenHoliday{ objChosenHoliday }, m_objUser(objUser), m_objChosenActivities{ objChosenActivities }{}
    //This sets the chosen holiday
    void setChosenHoliday(clsHoliday* objHoliday);
    //This sets the session user
    void setUser(std::shared_ptr<clsUser>objUser);
    //This removes the chosen activity by ID
    void removeChosenActivityByID(int iID);
    //This adds chosen activity 
    void addChosenActivity(clsActivity* objChosenActivities);


};
