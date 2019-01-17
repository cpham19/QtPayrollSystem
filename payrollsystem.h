#ifndef PAYROLLSYSTEM_H
#define PAYROLLSYSTEM_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QStandardItemModel>
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
        double getTotalAmount() const;
        void setTotalAmount(double amount);
        Employee getEmployeeById(QString id);
        QStringList getStringListOfEmployees() const;
        QStandardItemModel *getStandardItemModelOfEmployees() const;

        void issuePaycheck();
        vector<Employee> getPayrollList() const;

    private:
        QString nameOfCompany;
        vector<Employee> payrollList;
        double totalAmount;
};

#endif /* PAYROLLSYSTEM_H */

