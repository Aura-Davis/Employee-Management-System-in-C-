drop database if exists `Employee_Management`;
create database `Employee_Management`;
use `Employee_Management`;

create table employee
(
	EID int not null,
    emp_name varchar(50),
    emp_role varchar(50),
    hours int,
    primary key (EID)
);

create table activities
(
	EID int not null,
    activity varchar(15),
    primary key (EID)
);
