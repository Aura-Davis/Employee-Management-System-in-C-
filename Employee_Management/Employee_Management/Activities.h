#pragma once
#include <string>
#include <set>
class Activities
{
public:
    Activities(std::string HOST, std::string USER, std::string PASS, std::string DB);
    virtual ~Activities();
    int add_activity();
    int month_activity();
    int day_activity();
    int delete_activity();


protected:

private:
    std::string HOST, USER, PASS, DB;
};