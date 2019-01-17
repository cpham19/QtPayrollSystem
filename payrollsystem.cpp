#include "payrollsystem.h"
#include "paycheck.h"
#include <iostream>

using namespace std;

PayrollSystem::PayrollSystem() {
    totalAmount = 0.00;
}

QString PayrollSystem::getNameOfCompany() const {
    return nameOfCompany;
}

void PayrollSystem::setNameOfCompany(QString name) {
    nameOfCompany = name;
}

void PayrollSystem::addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours) {
    payrollList.push_back(Employee(id, fName, lName, gender, position, address, city, state, zipcode, wage, hours));
}

void PayrollSystem::editEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours) {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        if (payrollList[i].getEmployeeId().compare(id) == 0) {
            payrollList[i].setFirstName(fName);
            payrollList[i].setLastName(lName);
            payrollList[i].setGender(gender);
            payrollList[i].setJobPosition(position);
            payrollList[i].setStreetAddress(address);
            payrollList[i].setCity(city);
            payrollList[i].setState(state);
            payrollList[i].setZipcode(zipcode);
            payrollList[i].setHourlyWage(wage);
            payrollList[i].setNumberOfHours(hours);
        }
    }
}

void PayrollSystem::recordEmployeeHoursById(QString id, int hours) {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        if (payrollList[i].getEmployeeId().compare(id) == 0) {
            payrollList[i].setNumberOfHours(hours);
        }
    }
}

void PayrollSystem::removeEmployeeById(QString id) {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        if (payrollList[i].getEmployeeId().compare(id) == 0) {
            payrollList.erase(payrollList.begin() + i);
        }
    }
}

Employee PayrollSystem::getEmployeeById(QString id) {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        if (payrollList[i].getEmployeeId().compare(id) == 0) {
            return payrollList[i];
        }
    }
}

QStringList PayrollSystem::getStringListOfEmployees() const{
    QStringList list;

    for (Employee e: payrollList) {
        list << e.getEmployeeId() + " " + e.getFirstName() + " " + e.getLastName();
    }

    return list;
}

QStandardItemModel* PayrollSystem::getStandardItemModelOfEmployees() const{
    QStandardItemModel *tableViewModel = new QStandardItemModel((int) getPayrollList().size(), 11);
    tableViewModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Employee ID"));
    tableViewModel->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    tableViewModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    tableViewModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Gender"));
    tableViewModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Job Position"));
    tableViewModel->setHeaderData(5, Qt::Horizontal, QObject::tr("Street Address"));
    tableViewModel->setHeaderData(6, Qt::Horizontal, QObject::tr("City"));
    tableViewModel->setHeaderData(7, Qt::Horizontal, QObject::tr("State"));
    tableViewModel->setHeaderData(8, Qt::Horizontal, QObject::tr("Zipcode"));
    tableViewModel->setHeaderData(9, Qt::Horizontal, QObject::tr("Hourly Wage"));
    tableViewModel->setHeaderData(10, Qt::Horizontal, QObject::tr("Hours Worked"));

    for (int row = 0; row < (int) getPayrollList().size(); row++) {
        Employee e = getPayrollList()[row];
        for (int col = 0; col < 11; col++) {
            QModelIndex index = tableViewModel->index(row,col,QModelIndex());
            switch(col) {
                case 0:
                    tableViewModel->setData(index, e.getEmployeeId());
                    break;
                case 1:
                    tableViewModel->setData(index, e.getFirstName());
                    break;
                case 2:
                    tableViewModel->setData(index, e.getLastName());
                    break;
                case 3:
                    tableViewModel->setData(index, e.getGender());
                    break;
                case 4:
                    tableViewModel->setData(index, e.getJobPosition());
                    break;
                case 5:
                    tableViewModel->setData(index, e.getStreetAddress());
                    break;
                case 6:
                    tableViewModel->setData(index, e.getCity());
                    break;
                case 7:
                    tableViewModel->setData(index, e.getState());
                    break;
                case 8:
                    tableViewModel->setData(index, e.getZipcode());
                    break;
                case 9:
                    tableViewModel->setData(index, e.getHourlyWage());
                    break;
                case 10:
                    tableViewModel->setData(index, e.getNumberOfHours());
                    break;
                default:
                    break;
            }
        }
    }

    return tableViewModel;
}

void PayrollSystem::issuePaycheck() {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        Paycheck p = Paycheck(payrollList[i].getEmployeeId(), payrollList[i].getFirstName(), payrollList[i].getLastName(), payrollList[i].calcPay());
        totalAmount += p.getPayCheckAmount();
        payrollList[i].setNumberOfHours(0);
    }
}

vector<Employee> PayrollSystem::getPayrollList() const {
    return payrollList;
}

double PayrollSystem::getTotalAmount() const {
    return totalAmount;
}

void PayrollSystem::setTotalAmount(double amount) {
    totalAmount = amount;
}
