#include "Activities.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;

Activities::Activities(string HOST, string USER, string PASS, string DB)
{
    //ctor
    this->HOST = HOST;
    this->USER = USER;
    this->PASS = PASS;
    this->DB = DB;
}

Activities::~Activities()
{
    //dtor
}

int Activities::add_activity()
{
    char day[20];
    int hours, ID;

    cout << "Employee ID: ";
    cin >> ID;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput invalid. ID must consist of numbers.\n";
        cout << "Employee ID: ";
        cin >> ID;
    }
    cin.ignore(100, '\n');

    cout << "Date worked (in YYYY-MM-DD Format): ";
    cin.getline(day, 20, '\n');
    cout << "Hours worked: ";
    cin >> hours;
    
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput invalid. Hours must consist of numbers.\n";
        cout << "Hours worked: ";
        cin >> hours;
    }
    cin.ignore(100, '\n');
    string date = "'" + string(day) + "'";

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("insert into activities (EID, Date, Hours) values (" + to_string(ID) + ", " + date + ", " + to_string(hours) + " );");
        stmt->execute("update employee_management.employee set Hours = Hours + " + to_string(hours) +  " where EID = " + to_string(ID) + ";");
    }
    catch (sql::SQLException& e) {
        //exception handler
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return EXIT_FAILURE;
    }

    cout << "Activity Added.\n\n";
    return EXIT_SUCCESS;
}

int Activities::month_activity()
{
    char day[20];
    int ID;

    cout << "Employee ID: ";
    cin >> ID;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput invalid. ID must consist of numbers.\n";
        cout << "Employee ID: ";
        cin >> ID;
    }
    cin.ignore(100, '\n');

    cout << "Date (in YYYY-MM format): ";
    cin.getline(day, 20, '\n');
    string date = "'" + string(day) + "%'";

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        sql::ResultSet* res;
        res = stmt->executeQuery("select * from activities where EID = " + to_string(ID) + " and Date like " + date + ";");

        cout << endl;
        while (res->next())
        {
            cout << "Employee ID: " << res->getString("EID") << " ";
            cout << "Date: " << res->getString("Date") << " ";
            cout << "Hours: " << res->getString("Hours") << endl;
        }
        cout << endl;
    }
    catch (sql::SQLException& e) {
        //exception handler
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int Activities::day_activity()
{
    char day[20];
    cout << "Select Day (in YYYY-MM-DD Format): ";
    cin.getline(day, 20, '\n');
    string date = "'" + string(day) + "'";

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        sql::ResultSet* res;
        res = stmt->executeQuery("select * from activities where Date = " + date + ";");

        cout << endl;
        while (res->next())
        {
            cout << "Employee ID: " << res->getString("EID") << " ";
            cout << "Date: " << res->getString("Date") << " ";
            cout << "Hours: " << res->getString("Hours") << endl;
        }
        cout << endl;
    }
    catch (sql::SQLException& e) {
        //exception handler
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int Activities::delete_activity()
{
    int ID;
    char day[20];

    cout << "Employee ID: ";
    cin >> ID;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput invalid. ID must consist of numbers.\n";
        cout << "Employee ID: ";
        cin >> ID;
    }
    cin.ignore(100, '\n');

    cout << "Select Day (in YYYY-MM-DD Format): ";
    cin.getline(day, 20, '\n');
    string date = "'" + string(day) + "'";

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        sql::ResultSet* res;
        res = stmt->executeQuery("select * from activities where EID = " + to_string(ID) + " and Date = " + date + ";");

        while (res->next())
        {
            string hours = res->getString("Hours");
            stmt->execute("update employee_management.employee set Hours = Hours - " + hours + " where EID = " + to_string(ID) + ";");
        }

        stmt->execute("delete from activities where EID = " + to_string(ID) + " and Date = " + date + ";");
    }
    catch (sql::SQLException& e) {
        //exception handler
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return EXIT_FAILURE;
    }

    cout << "Activity Deleted.\n\n";
    return EXIT_SUCCESS;
}

