#pragma once
#include <string>
class clsActivity {
private:
    int m_iID;
    std::string m_sName;
    double m_dCostPerPerson;
    int m_iHolidayID;
    std::string m_sActivityType;
public:
    clsActivity() :m_iID(0), m_sName(""), m_dCostPerPerson(0), m_iHolidayID{ 0 } {
    }
    clsActivity(int iID, std::string sName, double dCostPerPerson, int iHolidayID, std::string sActivityType)
        : m_iID{ iID }, m_sName{ sName }, m_dCostPerPerson{ dCostPerPerson }, m_iHolidayID{ iHolidayID }, m_sActivityType{ sActivityType }{
    }

    double getCostPerPerson() { return m_dCostPerPerson; }
    int getLocationId() { return m_iHolidayID; }
    int getId() const { return m_iID; }
    std::string getName() { return m_sName; }
    std::string getActivityType()
    {
        return m_sActivityType;

    }
    ~clsActivity() {

    }

    
};

class clsCustomActivity : public clsActivity {
private:
    std::string m_sUsername;
public:

    std::string getUsername() { return m_sUsername; }

    clsCustomActivity(int iActivityID, std::string sActivityName, double dCostPerPerson, int iHolidayID, std::string sActivityType, std::string sUsername) :
        clsActivity(iActivityID, sActivityName, dCostPerPerson, iHolidayID, sActivityType), m_sUsername(sUsername) {
    }
   
};
