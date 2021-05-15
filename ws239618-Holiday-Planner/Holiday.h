#pragma once
#include <string>
#include <algorithm>
#include "HolidayActivity.h"
#include <vector>
class clsHoliday {
private:
    int m_iID;
    std::string m_sName;
    double m_dCostPerPerson;
    int m_iMinimumTravellers;

public:
    std::vector<clsActivity>m_objActivities;
    std::vector<clsCustomActivity>m_objCustomActivities;
    std::vector<clsActivity*>m_objStandardAndCustomActivities;
    void setStandardAndCustomActivities()
    {
        m_objStandardAndCustomActivities.clear();
        for (auto& objStandardActivity : m_objActivities) {
            m_objStandardAndCustomActivities.push_back(&objStandardActivity);
        }
        for (auto& objCustomActivity : m_objCustomActivities)
        {
            m_objStandardAndCustomActivities.push_back(&objCustomActivity);
        }
    }
    bool isHolidayAvailableForFamily(int iFamilySize) { return iFamilySize >= m_iMinimumTravellers; }
    int setUniqueIDForActivity() {
        std::vector<int> vAllActivityIDs;
        for (const auto& objActivity : m_objStandardAndCustomActivities) {
            vAllActivityIDs.push_back(objActivity->getId());
        }
        return *std::max_element(vAllActivityIDs.begin(), vAllActivityIDs.end()) + 1;

    }

    void clearCustomActivities()
    {
        m_objCustomActivities.clear();
    }

    void addCustomActivity(clsCustomActivity objActivity) {
        m_objCustomActivities.push_back(objActivity);
    }

    clsActivity findStandardActivityById(int iActivityID) {
        return *std::find_if(m_objActivities.begin(), m_objActivities.end(), [&](auto& objActivity) {
            return objActivity.getId() == iActivityID;
            });
    }
    auto findCustomActivityById(int iActivityID) {
        return *std::find_if(m_objCustomActivities.begin(), m_objCustomActivities.end(), [&](auto& objActivity) {
            return objActivity.getId() == iActivityID;
            });
    }
    void addActivity(clsActivity objActivity) { m_objActivities.push_back(objActivity); }
    int getId() { return m_iID; }
    int getMinimumTravellers() { return m_iMinimumTravellers; }
    void setMinimumTravellers(int iMinimumTravellers) { m_iMinimumTravellers = iMinimumTravellers; }
    double getCostPerPerson() { return m_dCostPerPerson; }
    std::string getName() { return m_sName; }
    clsHoliday() : m_iID{ 0 }, m_sName{ "" }, m_dCostPerPerson{ 0 }, m_iMinimumTravellers{ 0 } {}
    clsHoliday(int iID, std::string sName, double dCostPerPerson, int iMinimumTravellers)
        :m_iID{ iID }, m_sName{ sName }, m_dCostPerPerson{ dCostPerPerson }, m_iMinimumTravellers{ iMinimumTravellers } {}
};
