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
        int getCompanyId() const;
        QString getNameOfCompany() const;
        void setNameOfCompany(QString name);
        void addEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours, double totalAmountPaid, int totalNumberOfHours);
        void editEmployee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours);
        void recordEmployeeHoursById(QString id, int hours);
        void removeEmployeeById(QString id);
        double getTotalAmount() const;
        void setTotalAmount(double amount);
        void incrementHoursOfEmployees();
        Employee getEmployeeById(QString id);
        QStringList getEmployeesStringList() const;

        void issuePaychecks();
        vector<Employee> getPayrollList() const;

    private:
        QString nameOfCompany;
        int companyId;
        vector<Employee> payrollList;
        double totalAmount;
};

#endif /* PAYROLLSYSTEM_H */

