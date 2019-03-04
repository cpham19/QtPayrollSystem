#include "headers/payrollsystem.h"
#include "headers/paycheck.h"
#include "Headers/employee.h"
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

void PayrollSystem::addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, int totalNumberOfHours, int overtimeHours, int totalNumberOfOvertimeHours, double wage, double amountToBePaid, double totalAmountPaid) {
    payrollList.push_back(Employee(id, fName, lName, gender, position, address, city, state, zipcode, hours, totalNumberOfHours, overtimeHours, totalNumberOfOvertimeHours, wage, amountToBePaid, totalAmountPaid));
}

void PayrollSystem::editEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, double wage) {
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

Employee PayrollSystem::getEmployeeById(QString id) const{
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

        payrollList[i].setAmountToBePaid(0.00);

        totalAmount += p.getPayCheckAmount();
        double oldTotalAmount = e.getTotalAmountPaid();
        payrollList[i].setTotalAmountPaid(p.getPayCheckAmount() + oldTotalAmount);

        int oldTotalNumberOfHours = e.getTotalNumberOfHours();
        int currentNumberOfHours = e.getNumberOfHours();
        payrollList[i].setTotalNumberOfHours(currentNumberOfHours + oldTotalNumberOfHours);
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
    double amount = 0;
    for (int i = 0; i < (int) payrollList.size(); i++) {
        amount += payrollList[i].getTotalAmountPaid();
    }

    return amount;
}

double PayrollSystem::getBudget() const {
    return budget;
}

bool PayrollSystem::containCEO() const {
    for (Employee e: payrollList) {
        if (e.getJobPosition().compare("Chief Executive Officer") == 0) {
            return true;
        }
    }

    return false;
}

QString PayrollSystem::getCEO() {
    for (int i = 0; i < (int) payrollList.size(); i++) {
        if (payrollList[i].getJobPosition().compare("Chief Executive Officer") == 0) {
            return payrollList[i].getFirstName() + " " + payrollList[i].getLastName();
        }
    }

    return "None";
}

void PayrollSystem::setTotalAmount(double amount) {
    totalAmount = amount;
}

void PayrollSystem::setBudget(double amount) {
    budget = amount;
}

void PayrollSystem::incrementHoursOfEmployees() {
    for (int i = 0; i < (int) payrollList.size(); i++) {\
        Employee e = payrollList[i];
        int oldHours = e.getNumberOfHours();
        int newHours = oldHours + 1;
        payrollList[i].setNumberOfHours(newHours);

        double newAmountToBePaid = e.calcPay();
        payrollList[i].setAmountToBePaid(newAmountToBePaid);
    }
}

QJsonObject PayrollSystem::getNumberOfGenders() const {
    QJsonObject obj;

    obj.insert("Male", 0);
    obj.insert("Female", 0);

    foreach(const QString& key, obj.keys()) {
        for (Employee e : payrollList) {
            if (e.getGender().compare(key) == 0) {
                int oldValue = obj.value(key).toInt();
                obj[key] = oldValue + 1;
            }
        }
    }

    return obj;
}

QJsonObject PayrollSystem::getNumberOfPeopleWithPositions() const {
    QJsonObject obj;

    for (Employee e: payrollList) {
        if (!obj.contains(e.getJobPosition())) {
            obj.insert(e.getJobPosition(), 0);
        }
    }

    foreach(const QString& key, obj.keys()) {
        for (Employee e : payrollList) {
            if (e.getJobPosition().compare(key) == 0) {
                int oldValue = obj.value(key).toInt();
                obj[key] = oldValue + 1;
            }
        }
    }

    return obj;
}

QJsonObject PayrollSystem::getAverageSalariesOfPositions() const {
    QJsonObject obj;

    for (Employee e: payrollList) {
        if (!obj.contains(e.getJobPosition())) {
            obj.insert(e.getJobPosition(), 0.00);
        }
    }

    int counter = 0;
    int hoursPerWeek = 40;
    int weeks = 4;
    int months = 12;

    foreach(const QString& key, obj.keys()) {
        for (Employee e : payrollList) {
            if (e.getJobPosition().compare(key) == 0) {
                double oldTotalSalary = obj.value(key).toDouble();
                double salary = e.getHourlyWage() * hoursPerWeek * weeks * months;
                obj[key] = QString::number(salary + oldTotalSalary, 'f', 2).toDouble();
                counter++;
            }
        }
        double totalSalary = obj.value(key).toDouble();
        obj[key] = QString::number(totalSalary / counter, 'f', 2).toDouble();
        counter = 0;
    }

    return obj;
}
