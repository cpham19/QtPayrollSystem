#include "headers/paycheck.h"

Paycheck::Paycheck(QString id, QString fName, QString lName, double pay) : employeeId(id), firstName(fName), lastName(lName), paycheckAmount(pay) {
}

QString Paycheck::getEmployeeId() const {
    return employeeId;
}

QString Paycheck::getFirstName() const {
    return firstName;
}

QString Paycheck::getLastName() const {
    return lastName;
}

double Paycheck::getPayCheckAmount() const {
    return paycheckAmount;
}
