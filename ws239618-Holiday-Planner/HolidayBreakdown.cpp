#include "HolidayBreakdown.h"
void clsHolidayBreakdown::setActiveUserCustomActivities(std::vector<clsHoliday>& vHolidays)
{
    for (auto& objHoliday : vHolidays) {
        objHoliday.clearCustomActivities();
    }
    for (auto& objActivity : vAllCustomActivitiesByUsers) {
        //findHoliday(objActivity.getLocationId(), vHolidays)->clearCustomActivities();
        if (getUser()->get_username() == objActivity.getUsername())
        {
            findHoliday(objActivity.getLocationId(), vHolidays)->addCustomActivity(objActivity);
        }
    }
}

void clsHolidayBreakdown::loadAllCustomActivities(std::string sCustomActivitiesCSV) {
    vAllCustomActivitiesByUsers.clear();
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file(sCustomActivitiesCSV);
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
            vAllCustomActivitiesByUsers.push_back(clsCustomActivity{ stoi(objSplit.at(0)),objSplit.at(1), stod(objSplit.at(2)), stoi(objSplit.at(3)), objSplit.at(4), objSplit.at(5) });
        }
    }
}
std::vector<clsActivity*> clsHolidayBreakdown::getChosenActivities() {
    return m_objChosenActivities;
}
void clsHolidayBreakdown::clearSession() {
    //nulls out the pointer to clear session
    m_objUser = nullptr;
    m_objChosenHoliday = nullptr;
    m_objUserReports.clear();
    m_objAllReports.clear();
    allActivityData.clear();


}
bool clsHolidayBreakdown::updateHolidayPlanReport(std::string sHolidayName, clsReport objUpdatedReport, std::string holidayReportsCSV)
{
    //searches through vector to return the report
    auto objReport = std::find_if(m_objAllReports.begin(), m_objAllReports.end(), [&](auto& objReport) {
        return objReport.getHolidayName() == sHolidayName;
        });
    //if the report is found
    if (objReport != m_objAllReports.end())
    {
        //will subsequently update
        *objReport = objUpdatedReport;
        saveReportCSV(holidayReportsCSV);


        setActiveUserReports();

        return true;
    }
    //if not found return false
    return false;
}
bool clsHolidayBreakdown::doesHolidayPlanExist(std::string sHolidayName) {
    //searches through userReports vector and if it is not equal to the end of the vector then it means plan does exist
    if (std::find_if(m_objUserReports.begin(), m_objUserReports.end(), [&](auto& objReport) {
        return objReport.getHolidayName() == sHolidayName;
        }) != m_objUserReports.end()) {
        return true;
    }
    return false;
}

void clsHolidayBreakdown::addReport(clsReport objReport, std::string reportsCSV) {
    //pushes back report which is passed in through the parameters
    m_objAllReports.push_back(objReport);
    saveReportCSV(reportsCSV);
    setActiveUserReports();
}

int clsHolidayBreakdown::reportSize() {
    //casting report size to an int, to stay consistent with datatype usage
    return (int)m_objUserReports.size();
}
clsReport clsHolidayBreakdown::selectReport(int iIndex) {
    //this will return a report at the index specified in the report vector
    return m_objUserReports.at(iIndex);
}

void clsHolidayBreakdown::setActiveUserReports() {
    //Clears user reports, incase information from a previous user is there
    m_objUserReports.clear();
    //Will go through all the reports, and then assign the user reports
    for (auto& objReport : m_objAllReports)
    {
        if (objReport.getUsername() == m_objUser->get_username())
        {

            m_objUserReports.push_back(objReport);
        }
    }
    //m_objAllReports.clear();
}
void clsHolidayBreakdown::displayReportMenu() {

    int iCount = 1;
    //This will firstly set active user reports, so it can display said reports
    //setActiveUserReports();

    message("SAVED HOLIDAY REPORT MENU\n\n");
    //Loop through all of them to display all reports saved
    for (auto& objReport : m_objUserReports)
    {
        message(std::to_string(iCount++) + ". " + objReport.getHolidayName() + "\n");
    }
}
void clsHolidayBreakdown::saveReportCSV(std::string holidayReportsCSV)
{
    //Any changes made to the all reports vector, will be updated in the CSV file
    std::ofstream file;
    file.open(holidayReportsCSV);
    for (auto& objReport : m_objAllReports)
    {
        file << objReport.getUsername() << "," << objReport.getHolidayName()
            << "," << objReport.getTotalPrice() << "," << objReport.getDiscount() << "," << objReport.getVAT() << ","
            << objReport.getAdultCount() << "," << objReport.getChildCount() << ",\n";
    }
    file.close();
    //updating all information regarding selected activities in the in the CSV
    std::ofstream file2;
    file2.open("addingActivitiesToReport.csv");
    for (auto& objReport : m_objAllReports) {
        for (auto& objActivity : objReport.m_objAddedActivities) {
            file2 << objReport.getUsername() << "," << objReport.getHolidayName() << "," << objActivity->getId() << "," << objActivity->getActivityType() << ",\n";
        }
    }
    file2.close();
}
void clsHolidayBreakdown::loadAllActivityData(std::vector<clsHoliday>& vAllHolidays) {
    //load all activity data, firstly, clearing the vector to ensure everything will be renewed
    allActivityData.clear();
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file("addingActivitiesToReport.csv");
    std::vector<std::string>objS;

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
            //sets information from CSV and applies them in the object
            allActivityData.push_back({ objSplit.at(0), objSplit.at(1), stoi(objSplit.at(2)), objSplit.at(3) });
        }
    }

}
auto clsHolidayBreakdown::findSavedReportByHolidayName(std::string sHolidayLocation) {
    //searches through the report to find saved report, returns iterator
    return std::find_if(m_objAllReports.begin(), m_objAllReports.end(), [&](auto& objReport) {
        return objReport.getHolidayName() == sHolidayLocation;
        });


}
void clsHolidayBreakdown::assignSavedActivities(std::vector<clsHoliday>& vAllHolidays)
{
    //Searches through activity data, finds ids and names, and unique applies them to the holiday report they saved
    for (auto& objActivityData : allActivityData) {

        for (auto& objReport : m_objAllReports) {
            if (objReport.getUsername() == objActivityData.sUserName && objReport.getHolidayName() == objActivityData.sLocationName) {
                //confirmYesOrNo(objActivityData.sActivityType);
                if (objActivityData.sActivityType == "Standard") {
                    //HERE, I am using polymorphism the "new" keyboard to achieve dynamic polymorphism
                    clsActivity* objActivity = new clsActivity(findHolidayByName(objActivityData.sLocationName, vAllHolidays).findStandardActivityById(objActivityData.iActivityID));
                    objReport.addAddedActivity(objActivity);
                }
                else if (objActivityData.sActivityType == "Custom") {
                    clsActivity* objActivity = new clsCustomActivity(findHolidayByName(objActivityData.sLocationName, vAllHolidays).findCustomActivityById(objActivityData.iActivityID));
                    objReport.addAddedActivity(objActivity);
                }


            }
        }

    }


    //for (auto&objActivityData : allActivityData) 
    //{
    //    auto savedReport = findSavedReportByHolidayName(objActivityData.sLocationName);
    //    auto holiday = findHolidayByName(objActivityData.sLocationName, vAllHolidays);

    //    savedReport->addAddedActivity(*holiday.findActivityByID(objActivityData.iActivityID));
        /*for (auto& objActivity : holiday.m_objActivities) {
            if (objActivity.get_id() == objActivityData.iActivityID)
            {
                savedReport->addAddedActivity(objActivity);

            }
        }*/

        // savedReport->addAddedActivity(activity);
         //findActivityByID(objActivityData.iActivityID));
}


//for (auto &objReport : m_objAllReports)
//  {
//      std::vector<clsActivity>vAddedActivities(0);
//      for (auto& objActivityData : allActivityData) 
//      {
//          
//          if (getUser()->get_username() == objActivityData.sUserName) {
//              for (auto& activity : findHolidayByName(objActivityData.sLocationName, vAllHolidays).m_objActivities) 
//              {
//                  if (activity.get_id() == objActivityData.iActivityID) {
//                      vAddedActivities.push_back(activity);
//                  }
//              }
//              objReport.setAddedActivities(vAddedActivities);
//              vAddedActivities.clear();
//          }
//      }
//  }
  /*for (auto& objReport : objTrip.m_objAllReports) {
      if (objReport.getHolidayName() == objSplit.at(1))
      {
          for (auto& objActivity : findHolidayByName(objSplit.at(1), vAllHolidays).m_objActivities)
          {
              if (objActivity.get_id() == stoi(objSplit.at(3)))
              {
                  objReport.addAddedActivity(objActivity);
              }
          }
      }
  }*/




void clsHolidayBreakdown::loadAllReportsCSV(std::string holidayReports) {
    //clears all reports
    m_objAllReports.clear();
    std::vector<std::string>objSplit;
    std::string sLine = "";
    std::string sResult = "";
    std::ifstream file(holidayReports);
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

            m_objAllReports.push_back(clsReport(objSplit.at(0), objSplit.at(1), stod(objSplit.at(2)), stod(objSplit.at(3)), stod(objSplit.at(4)), stoi(objSplit.at(5)), stoi(objSplit.at(6))));

        }
    }


}

double clsHolidayBreakdown::totalActivityCost(int iOption)
{
    return getChosenHoliday()->m_objStandardAndCustomActivities.at((std::size_t)iOption)->getCostPerPerson() * getUser()->familySize();
}

double clsHolidayBreakdown::totalActivityCost() {
    double dSum = 0;
    for (auto& objActivity : m_objChosenActivities) {
        dSum += objActivity->getCostPerPerson() * m_objUser->familySize();
    }
    return dSum;
}

void clsHolidayBreakdown::deleteSavedReport(clsReport objPassedInReport) {
    auto it = std::find_if(m_objAllReports.begin(), m_objAllReports.end(), [&](auto& objReport) {
        return objReport.getHolidayName() == objPassedInReport.getHolidayName() && objReport.getUsername() == objPassedInReport.getUsername();
        });
    m_objAllReports.erase(it);

}
void clsHolidayBreakdown::displayChosenActivities()
{
    if (m_objChosenActivities.size() != 0)
    {
        for (std::size_t stCount = 0; stCount < m_objChosenActivities.size(); stCount++)
        {
            std::string sActivityName = m_objChosenActivities.at(stCount)->getName();
            message("\n  ACTIVITY " + std::to_string(stCount + 1) + "\n");
            message("Name: " + sActivityName + "\n");
            message("Cost per person: " + static_cast<std::string>(char(156) + toStringWithPrecision(m_objChosenActivities.at(stCount)->getCostPerPerson(), 2) + "\n"));
            message("  Total " + sActivityName + " cost for family: "
                + char(156) + toStringWithPrecision((m_objChosenActivities.at(stCount)->getCostPerPerson() * m_objUser->familySize()), 2) + "\n");

        }
        message("\n  Total activity(s) cost: " + static_cast<std::string>(char(156) + toStringWithPrecision(totalActivityCost(), 2) + "\n"));
    }
    else
    {
        message("You haven't included any activities for your " + m_objChosenHoliday->getName() + " holiday\n");
    }
}




void clsHolidayBreakdown::setChosenHoliday(clsHoliday* objHoliday) {
    m_objChosenHoliday = objHoliday; m_objChosenActivities.clear();
}
void clsHolidayBreakdown::setUser(std::shared_ptr<clsUser>objUser) {
    m_objUser = objUser;
}
void clsHolidayBreakdown::removeChosenActivityByID(int iID) {
    auto toBeDeleted = std::find_if(m_objChosenActivities.begin(), m_objChosenActivities.end(), [&](clsActivity*& objActivity) {
        return objActivity->getId() == iID;
        });
    if (toBeDeleted != m_objChosenActivities.end()) {
        m_objChosenActivities.erase(toBeDeleted);
    }
}
clsHoliday* clsHolidayBreakdown::getChosenHoliday() const { return m_objChosenHoliday; }
void clsHolidayBreakdown::addChosenActivity(clsActivity* objChosenActivities) { m_objChosenActivities.push_back(objChosenActivities); }
std::shared_ptr<clsUser> clsHolidayBreakdown::getUser() const
{

    return m_objUser;
}