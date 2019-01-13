#ifndef PAYROLLSYSTEM_H
#define PAYROLLSYSTEM_H

#include <vector>
#include <QString>
#include <QStringList>
#include "employee.h"
#include "paycheck.h"

using namespace std;

class PayrollSystem {
    public:
        PayrollSystem();
        QString getNameOfCompany() const;
        void setNameOfCompany(QString name);
        void addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours);
        void editEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours);
        void recordEmployeeHoursById(QString id, int hours);
        void removeEmployeeById(QString id);
        Employee getEmployeeById(QString id);
        QStringList getStringListOfEmployees() const;
        void issuePaycheck();
        vector<Employee> getPayrollList() const;

    private:
        QString nameOfCompany;
        vector<Employee> payrollList;
};

#endif /* PAYROLLSYSTEM_H */

