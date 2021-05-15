#include "pch.h"
#include "CppUnitTest.h"
#include "../ws239618-Holiday-Planner/Holiday.h"
#include "../ws239618-Holiday-Planner/User.h"
#include "../ws239618-Holiday-Planner/HolidayActivity.h"
#include "../ws239618-Holiday-Planner/HolidayReport.h"
#include "../ws239618-Holiday-Planner/HolidayBreakdown.h"
#include <string>
#include <vector>
#include <memory>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HolidayPlannerUnitTest
{
	TEST_CLASS(Users)
	{
	public:
		clsUser _objUser;
		//START OF TEST DATA FOR USER CLASS
		std::string sName = "George Bradley";
		int iAdultCount = 2;
		int iChildCount = 2;
		std::string sUsername = "gb";
		std::string sPassword = "Password321";
		//END OF TEST DATA FOR USER CLASS
		TEST_METHOD(settingUserName)
		{
			_objUser.setName(sName);
			Assert::AreEqual(sName, _objUser.get_name());
		}
		TEST_METHOD(settingAdultCount)
		{
			_objUser.setAdultCount(iAdultCount);
			Assert::AreEqual(iAdultCount, _objUser.getAdultCount());
		}
		TEST_METHOD(settingChildCount)
		{
			_objUser.setChildCount(iChildCount);
			Assert::AreEqual(iChildCount, _objUser.getChildCount());
		}
		TEST_METHOD(UserConstructor)
		{
			clsUser objNewUser(sName, sUsername, sPassword, iAdultCount, iChildCount);
			Assert::AreEqual(sName, objNewUser.get_name());
			Assert::AreEqual(sUsername, objNewUser.get_username());
			Assert::AreEqual(sPassword, objNewUser.get_password());
			Assert::AreEqual(iAdultCount, objNewUser.getNumberOfAdultsInFamily());
			Assert::AreEqual(iChildCount, objNewUser.getNumberOfChilrenInFamily());
		}
		TEST_METHOD(SetName) {
			_objUser.setName(sName);
			Assert::AreEqual(sName, _objUser.get_name());
		}
		TEST_METHOD(SetChildCount) {
			_objUser.setChildCount(iChildCount);
			Assert::AreEqual(iChildCount, _objUser.getChildCount());
		}
		TEST_METHOD(SetAdultCount) {
			_objUser.setAdultCount(iAdultCount);
			Assert::AreEqual(iAdultCount, _objUser.getAdultCount());
		}
		TEST_METHOD(FamilySize)
		{
			int iTotalFamilySize = iAdultCount + iChildCount;
			_objUser.setAdultCount(iAdultCount);
			_objUser.setChildCount(iChildCount);
			Assert::AreEqual(_objUser.familySize(), iTotalFamilySize);
		}

	};

	TEST_CLASS(HolidayAndActivity)
	{
	public:

		//START OF VARIABLES TO FEED INFORMATION TO HOLIDAY 
		int iHolidayID = 1;
		std::string sNameOfHoliday = "Florida";
		double dCostPerPersonForHoliday = 100.00;
		int iMinimumTravellers = 3;
		//END OF VARIABLES TO FEED INFORMATION TO HOLIDAY
		//START OF VARIABLES TO FEED INFORMATION TO ACTIVITY
		int iCustomActivityID = 1;
		int iStandardActivityID = 1;
		std::string sActivityName = "Water Park";
		double dCostPerPersonForActivity = 200.00;
		std::string sActivityType = "Custom";
		std::string sUsername = "GB";
		//END OF VARIABLES TO FEED INFORMATION TO ACTIVITY
		clsHoliday _objHoliday;
		clsActivity _objStandardActivity;

		TEST_METHOD(TestHolidayArgumentConstructor)
		{
			clsHoliday objNewHoliday(iHolidayID, sNameOfHoliday, dCostPerPersonForHoliday, iMinimumTravellers);
			Assert::AreEqual(sNameOfHoliday, objNewHoliday.getName());
			Assert::AreEqual(dCostPerPersonForHoliday, objNewHoliday.getCostPerPerson());
			Assert::AreEqual(iMinimumTravellers, objNewHoliday.getMinimumTravellers());
		}
		TEST_METHOD(addCustomActivity) {

			clsCustomActivity objCustomActivity(iCustomActivityID, sActivityName, dCostPerPersonForActivity, iHolidayID, sActivityType, sUsername);
			_objHoliday.addCustomActivity(objCustomActivity);
			Assert::AreEqual(_objHoliday.m_objCustomActivities.at(0).getName(), sActivityName);
			Assert::AreEqual(_objHoliday.m_objCustomActivities.at(0).getId(), iCustomActivityID);
			Assert::AreEqual(_objHoliday.m_objCustomActivities.at(0).getCostPerPerson(), dCostPerPersonForActivity);
			Assert::AreEqual(_objHoliday.m_objCustomActivities.at(0).getActivityType(), sActivityType);
			Assert::AreEqual(_objHoliday.m_objCustomActivities.at(0).getUsername(), sUsername);
		}
		TEST_METHOD(AddStandardActivity)
		{
			clsActivity objActivity(1, "Hello", 100.00, 1, "Hello");
			clsHoliday objHoliday(iHolidayID, sNameOfHoliday, dCostPerPersonForHoliday, iMinimumTravellers);
			objHoliday.addActivity(objActivity);
			Assert::AreEqual(objActivity.getName(), objHoliday.m_objActivities.at(0).getName());
			Assert::AreEqual(objActivity.getLocationId(), objHoliday.m_objActivities.at(0).getLocationId());
			Assert::AreEqual(objActivity.getId(), objHoliday.m_objActivities.at(0).getId());
			Assert::AreEqual(objActivity.getCostPerPerson(), objHoliday.m_objActivities.at(0).getCostPerPerson());
			Assert::AreEqual(objActivity.getActivityType(), objHoliday.m_objActivities.at(0).getActivityType());
		}

		TEST_METHOD(findActivityByID) {
			clsActivity objTestActivity(iStandardActivityID, sActivityName, dCostPerPersonForActivity, iHolidayID, sActivityType);
			_objHoliday.addActivity(objTestActivity);
			Assert::AreEqual(_objHoliday.findStandardActivityById(1).getName(), sActivityName);
		}
		TEST_METHOD(IsHolidayAvailableToFamily) {
			clsUser objUser;
			objUser.setChildCount(1);
			objUser.setAdultCount(1);
			_objHoliday.setMinimumTravellers(4);
			Assert::IsFalse(_objHoliday.isHolidayAvailableForFamily(objUser.familySize()));
		}
	};


	TEST_CLASS(HolidayReport)
	{
	public:
		std::string sUsername;
		std::string sHolidayName;

		double dTotalPrice = 100.00;
		double dVAT = 0.20;
		double dDiscount = 0.25;
		int iAdultCount = 2;
		int iChildCount = 2;
		TEST_METHOD(HolidayReportConstructor) 
		{
			clsReport objReport(sUsername, sHolidayName, dTotalPrice, dVAT, dDiscount, iAdultCount, iChildCount);
			Assert::AreEqual(sUsername, objReport.getUsername());
			Assert::AreEqual(sHolidayName, objReport.getHolidayName());
			Assert::AreEqual(dTotalPrice, objReport.getTotalPrice());
			Assert::AreEqual(dVAT, objReport.getVAT());
			Assert::AreEqual(dDiscount, objReport.getDiscount());
			Assert::AreEqual(iAdultCount, objReport.getAdultCount());
			Assert::AreEqual(iChildCount, objReport.getChildCount());

		}
	};
	TEST_CLASS(HolidayBreakdown)
	{
	public:

		//START OF VARIABLES TO FEED INFORMATION TO HOLIDAY 
		int iHolidayID = 1;
		std::string sNameOfHoliday = "Florida";
		double dCostPerPersonForHoliday = 100.00;
		int iMinimumTravellers = 3;
		//END OF VARIABLES TO FEED INFORMATION TO HOLIDAY

		//START OF TEST DATA FOR USER CLASS
		std::string sName = "George Bradley";
		int iAdultCount = 2;
		int iChildCount = 2;
		std::string sUsername = "gb";
		std::string sPassword = "Password321";
		//END OF TEST DATA FOR USER CLASS

				//START OF VARIABLES TO FEED INFORMATION TO ACTIVITY
		int iCustomActivityID = 1;
		int iStandardActivityID = 1;
		std::string sActivityName = "Water Park";
		double dCostPerPersonForActivity = 200.00;
		std::string sActivityType = "Custom";
	
		//END OF VARIABLES TO FEED INFORMATION TO ACTIVITY
		TEST_METHOD(HolidayBreakdownConstructor)
		{
			clsUser objUser(sName, sUsername, sPassword, iAdultCount, iChildCount);
			clsHoliday objHoliday(iHolidayID, sNameOfHoliday, dCostPerPersonForHoliday, iMinimumTravellers);

			std::vector<clsActivity*>vActivities(0);
			for (int iCount = 0; iCount < 5; iCount++) {
				vActivities.push_back(&clsActivity(iCount, sName, dCostPerPersonForActivity, iHolidayID, sActivityType));
			}

			
			
			
		}
	};

}
