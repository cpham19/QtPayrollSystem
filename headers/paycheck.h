#ifndef PAYCHECK_H
#define PAYCHECK_H

#include <QString>

class Paycheck {
    public:
        Paycheck(QString id, QString fName, QString lName, double paycheckAmount);
        QString getEmployeeId() const;
        QString getFirstName() const;
        QString getLastName() const;
        double getPayCheckAmount() const;
    private:
        QString employeeId;
        QString firstName;
        QString lastName;
        double paycheckAmount;
};

#endif
