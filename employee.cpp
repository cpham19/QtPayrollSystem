#include "employee.h"

Employee::Employee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours) : employeeId(id), firstName(fName), lastName(lName), gender(gender), jobPosition(position), streetAddress(address), city(city), state(state), zipcode(zipcode), hourlyWage(wage), numberOfHours(hours) {
}

QString Employee::getEmployeeId() const {
    return employeeId;
}

QString Employee::getFirstName() const {
    return firstName;
}

QString Employee::getLastName() const {
    return lastName;
}
QString Employee::getGender() const {
    return gender;
}

QString Employee::getJobPosition() const {
    return jobPosition;
}

QString Employee::getStreetAddress() const {
    return streetAddress;
}

QString Employee::getCity() const {
    return city;
}

QString Employee::getState() const {
    return state;
}

QString Employee::getZipcode() const {
    return zipcode;
}

double Employee::getHourlyWage() const {
    return hourlyWage;
}

int Employee::getNumberOfHours() const {
    return numberOfHours;
}

void Employee::setFirstName(QString fName) {
    firstName = fName;
}

void Employee::setLastName(QString lName) {
    lastName = lName;
}

void Employee::setGender(QString g) {
    gender = g;
}

void Employee::setStreetAddress(QString address) {
    streetAddress = address;
}

void Employee::setCity(QString c) {
    city = c;
}

void Employee::setState(QString s) {
    state = s;
}

void Employee::setZipcode(QString z) {
    zipcode = z;
}

void Employee::setHourlyWage(double wage) {
    hourlyWage = wage;
}

void Employee::setNumberOfHours(int hours) {
    numberOfHours = hours;
}

double Employee::calcPay() const {
    return hourlyWage * numberOfHours;
}
