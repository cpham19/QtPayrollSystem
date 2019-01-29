#ifndef PAYCHECK_H
#define PAYCHECK_H

#include <QString>
using namespace std;

class Paycheck {
    public:
        Paycheck(QString id, QString fName, QString lName, double paycheckAmount);
        QString getEmployeeId() const;
        QString getFirstName() const;
        QString getLastName() const;
        double getPayCheckAmount() const;
        friend ostream &operator<<(ostream &output, const Paycheck &p);
    private:
        QString employeeId;
        QString firstName;
        QString lastName;
        double paycheckAmount;
};

#endif
