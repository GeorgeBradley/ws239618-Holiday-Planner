#pragma once

#include "HolidayActivity.h"
#include <vector>
class clsReport
{
private:
    std::string m_sUsername;
    std::string m_sHolidayName;
    double m_dTotalPrice;
    double m_dVAT;
    double m_dDiscount;
    int m_iAdultCount;
    int m_iChildCount;

public:
    std::vector<clsActivity*>m_objAddedActivities;
    
    clsReport(std::string sUsername, std::string sHolidayName, double dTotalPrice, double dVAT, double dDiscount, int iAdultCount, int iChildCount) {
        m_sUsername = sUsername;
        m_sHolidayName = sHolidayName;
        m_dTotalPrice = dTotalPrice;
        m_dVAT = dVAT;
        m_dDiscount = dDiscount;
        m_iAdultCount = iAdultCount;
        m_iChildCount = iChildCount;
    }


    clsReport(std::vector<clsActivity*>vActivities, std::string sUsername, std::string sHolidayName, double dTotalPrice, double dVAT, double dDiscount, int iAdultCount, int iChildCount)
    {
        m_objAddedActivities = vActivities;
        m_sUsername = sUsername;
        m_sHolidayName = sHolidayName;
        m_dTotalPrice = dTotalPrice;
        m_dVAT = dVAT;
        m_dDiscount = dDiscount;
        m_iAdultCount = iAdultCount;
        m_iChildCount = iChildCount;
    }
    ~clsReport(){

    }
    void addAddedActivity(clsActivity* objActivity) {
        m_objAddedActivities.push_back(objActivity);
    }
    void setAddedActivities(std::vector<clsActivity*>vAddedActivities) {
        m_objAddedActivities = vAddedActivities;
    }

    std::string getUsername() { return m_sUsername; }
    std::string getHolidayName() { return m_sHolidayName; }
    double getTotalPrice() { return m_dTotalPrice; }
    double getVAT() { return m_dVAT; }
    double getDiscount() { return m_dDiscount; }
    int getAdultCount() { return m_iAdultCount; }
    int getChildCount() { return m_iChildCount; }
};