#include "headers/payrollsystem.h"
#include "headers/paycheck.h"
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

void PayrollSystem::addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours, double totalAmountPaid, int totalNumberOfHours) {
    payrollList.push_back(Employee(id, fName, lName, gender, position, address, city, state, zipcode, wage, hours, totalAmountPaid, totalNumberOfHours));
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

QStringList PayrollSystem::getEmployeesStringList() const{
    QStringList list;

    for (Employee e: payrollList) {
        list << e.getEmployeeId() + " " + e.getFirstName() + " " + e.getLastName();
    }

    return list;
}

void PayrollSystem::issuePaychecks() {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        Employee e = payrollList[i];
        Paycheck p = Paycheck(e.getEmployeeId(), e.getFirstName(), e.getLastName(), e.calcPay());
        totalAmount += p.getPayCheckAmount();
        payrollList[i].setTotalNumberOfHours(e.getNumberOfHours());
        payrollList[i].setTotalAmountPaid(p.getPayCheckAmount());
        payrollList[i].setNumberOfHours(0);
    }
}

int PayrollSystem::getCompanyId() const {
    return companyId;
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

void PayrollSystem::incrementHoursOfEmployees() {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        int oldHours = payrollList[i].getNumberOfHours();
        int newHours = oldHours + 1;
        payrollList[i].setNumberOfHours(newHours);
    }
}
