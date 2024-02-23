#pragma once
#include <string>
#include <set>
class Employee
{
public:
    Employee(std::string HOST, std::string USER, std::string PASS, std::string DB);
    virtual ~Employee();
    int add_employee();
    int delete_employee();
    int show_information();

protected:

private:
    std::string HOST, USER, PASS, DB;
};
