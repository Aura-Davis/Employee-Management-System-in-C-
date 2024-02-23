#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Employee.h"
#include "Activities.h"

using namespace std;

int get_choice()
{
    cout << "Type number then press enter to select choice\n";
    cout << "1) Add Employee\n" << "2) Delete Employee\n" << "3) Log Employee Work Time\n";
    cout << "4) Show Employee Work History for Selected Month\n" << "5) Show Activity for All Employees for Selected Day\n";
    cout << "6) Show Information for Selected Employee\n" << "7) Delete Work Activity for Selected Day\n";
    cout << "8) Exit\n";
    int choice;
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput invalid. Please enter a number 1 - 8 and press enter\n";
        return get_choice();
    }
    cin.ignore(100, '\n');
    return choice;
}

int main()
{
    string HOST = "localhost", USER = "root", PASS = "V7w6dwXZsFXbyV5", DB = "Employee_Management";
    Employee* emp = new Employee(HOST, USER, PASS, DB);
    Activities* act = new Activities(HOST, USER, PASS, DB);
    bool recurse = true;
    int choice;
    
    while (recurse)
    {
        choice = get_choice();
        switch (choice)
        {
            case 1: emp->add_employee();
                break;
            case 2: emp->delete_employee();
                break;
            case 3: act->add_activity();
                break;
            case 4: act->month_activity();
                break;
            case 5: act->day_activity();
                break;
            case 6: emp->show_information();
                break;
            case 7: act->delete_activity();
                break;
            case 8: recurse = false;
                break;
        }
    }

    return EXIT_SUCCESS;
}