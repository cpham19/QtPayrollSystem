#ifndef PAYROLLSYSTEM_H
#define PAYROLLSYSTEM_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QJsonObject>
#include "employee.h"
#include "paycheck.h"

using namespace std;

class PayrollSystem {
    public:
        PayrollSystem();
        int getCompanyId() const;
        QString getNameOfCompany() const;
        void setNameOfCompany(QString name);
        void addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, int totalNumberOfHours, int overtimeHours, int totalNumberOfOvertimeHours, double wage, double amountToBePaid, double totalAmountPaid);
        void editEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, double wage);
        void removeEmployeeById(QString id);
        void payEmployeeById(QString id);
        double getTotalAmount() const;
        void setTotalAmount(double amount);
        double getBudget() const;
        void setBudget(double amount);
        void incrementHoursOfEmployees(QString dateString);
        Employee getEmployeeById(QString id) const;
        QStringList getEmployeesStringList() const;
        QJsonObject getNumberOfGenders() const;
        QJsonObject getNumberOfPeopleWithPositions() const;
        QJsonObject getAverageSalariesOfPositions() const;

        QString getCEO();
        bool containCEO() const;
        QJsonObject checkForOfficers();

        void issuePaychecks();
        vector<Employee> getPayrollList() const;

    private:
        QString nameOfCompany;
        int companyId;
        vector<Employee> payrollList;
        double totalAmount;
        double budget;
};

#endif /* PAYROLLSYSTEM_H */

