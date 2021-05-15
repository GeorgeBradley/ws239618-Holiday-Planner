#pragma once
#include <string>
/// <summary>
/// This is an abstract class which models a basic person
/// </summary>
class clsPerson {
private:
    std::string m_sName;
public:
    clsPerson() :m_sName("") {

    }
    clsPerson(std::string sName) :m_sName{ sName }{}

    std::string get_name() { return m_sName; }
 
    void setName(std::string sName) { m_sName = sName; }
};

/// <summary>
/// This is error checking to ensure what the user enters is an integer
/// </summary>
/// <param name="sMessage"></param>
/// <param name="sOption"></param>
/// <param name="iOption"></param>
/// <param name="iMenuItemSize"></param>
/// <returns></returns>


/// <summary>
/// The clsUSer class inherits all the attributes and functions from the clsPerson class. This will be used to model a user of a system
/// </summary>
class clsUser : public clsPerson {
private:

    std::string m_sUsername;
    std::string m_sPassword;
    int m_iNumberOfAdultsInFamily;
    int m_iNumberOfChildrenInFamily;

public:
    clsUser()
        :clsPerson(), m_sUsername(""), m_sPassword(""), m_iNumberOfAdultsInFamily(0), m_iNumberOfChildrenInFamily(0)
    {
    }

    clsUser(std::string sName, std::string sUsername, std::string sPassword, int iNumberOfAdultsInFamily, int iNumberOfChildrenInFamily)
        :clsPerson(sName), m_sUsername(sUsername), m_sPassword(sPassword),
        m_iNumberOfAdultsInFamily(iNumberOfAdultsInFamily), m_iNumberOfChildrenInFamily(iNumberOfChildrenInFamily)
    {
    }
    ~clsUser(){

    }
    std::string get_username() const { return m_sUsername; }
    std::string get_password() const { return m_sPassword; }
    int getNumberOfAdultsInFamily() const { return m_iNumberOfAdultsInFamily; }
    int getNumberOfChilrenInFamily() const { return m_iNumberOfChildrenInFamily; }

    void setAdultCount(int iAdultCount) { m_iNumberOfAdultsInFamily = iAdultCount; }
    void setChildCount(int iChildCount) { m_iNumberOfChildrenInFamily = iChildCount; }
    int getAdultCount() const { return m_iNumberOfAdultsInFamily; }
    int getChildCount() const { return m_iNumberOfChildrenInFamily; }
    int familySize() const { return m_iNumberOfAdultsInFamily + m_iNumberOfChildrenInFamily; }
};




