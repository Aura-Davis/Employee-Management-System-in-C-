#include "Employee.h"
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

Employee::Employee(string HOST, string USER, string PASS, string DB)
{
    //ctor
    this->HOST = HOST;
    this->USER = USER;
    this->PASS = PASS;
    this->DB = DB;
}

Employee::~Employee()
{
    //dtor
}

int Employee::add_employee()
{
    char name[20], role[20];
    int hours = 0, ID;

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
    cout << "Employee Name: ";
    cin.getline(name, 20, '\n');
    cout << "Employee Role: ";
    cin.getline(role, 20, '\n');
    string sname = "'" + string(name) + "'";
    string srole = "'" + string(role) + "'";

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("insert into employee (EID, Name, Role, Hours) values (" + to_string(ID) + ", " + sname + ", " + srole + ", " + to_string(hours) + " ); ");
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

    cout << "Employee Added.\n\n";
    return EXIT_SUCCESS;
}

int Employee::delete_employee()
{
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

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        stmt->execute("delete from employee where EID = " + to_string(ID) + ";");
        stmt->execute("delete from activities where EID = " + to_string(ID) + ";");
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

    cout << "Employee Deleted.\n\n";
    return EXIT_SUCCESS;
}

int Employee::show_information()
{
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

    try {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(this->HOST, this->USER, this->PASS));
        con->setSchema(this->DB);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        sql::ResultSet* res;
        res = stmt->executeQuery("select * from employee_management.employee where EID = " + to_string(ID) + ";");
        
        
        
        cout << endl;
        while (res->next()) 
        {
            cout << "Employee ID: " << res->getString("EID") << endl;
            cout << "Name: " << res->getString("Name") << endl;
            cout << "Role: " << res->getString("Role") << endl;
            cout << "Hours Worked: " << res->getString("Hours") << endl;
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