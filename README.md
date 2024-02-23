# Employee-Management-System-in-C-
An employment management system written in C++ and MySQL

This is a project which lets create and manage employees and their work hours. It is written in C++ and uses a MySQL database to store information. To use this you need Microsoft Visual Studio installed if running on windows along with MySQL and MySQL Connector/C++. The menu gives 8 choices: 
1) Add Employee
2) Delete Employee
3) Log Employee Work Time
4) Show Employee Work History for Selected Month
5) Show Activity for All Employees for Selected Day
6) Show Information for Selected Employee
7) Delete Work Activity for Selected Day
8) Exit

"Add Employee" allows you to create an employee with an employee ID, name, role (job position), and a default hours field is created which you can later increment with menu option 3. "Delete Employee" lets delete any existing employee. It deletes their information and work history from the database. "Log Employee Work Time" lets you add work activity for an employee into the database which can be searched for using menu options 4 and 5, or deleted with option 7. It also increments their hours worked which can be checked using menu option 6. "Show Employee Work History for Selected Month" shows you all the work activity of a specified employee for a specified month. "Show Acitivity for All Employees for Selected Day" shows you work activity for all employees on a specified day. "Show Information for Selected Employee" shows you employee ID number, name, role, and hours worked by a specified employee. "Delete Work Activity for Selected Day" allows you to delete the work history for a specified employee on a specified day. "Exit" allows you to exit the program.
