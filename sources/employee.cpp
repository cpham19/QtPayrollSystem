#include "headers/employee.h"

Employee::Employee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, int totalHours, int overtimeHours, int totalOvertimeHours, double wage, double amountPaid, double totalPaid) : employeeId(id), firstName(fName), lastName(lName), gender(gender), jobPosition(position), streetAddress(address), city(city), state(state), zipcode(zipcode), numberOfHours(hours), totalNumberOfHours(totalHours), numberOfOvertimeHours(overtimeHours), totalNumberOfOvertimeHours(totalOvertimeHours), hourlyWage(wage), amountToBePaid(amountPaid), totalAmountPaid(totalPaid) {
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

int Employee::getNumberOfHours() const {
    return numberOfHours;
}

int Employee::getTotalNumberOfHours() const {
    return totalNumberOfHours;
}

int Employee::getNumberOfOvertimeHours() const {
    return numberOfOvertimeHours;
}

int Employee::getTotalNumberOfOvertimeHours() const {
    return totalNumberOfOvertimeHours;
}

double Employee::getHourlyWage() const {
    return hourlyWage;
}

double Employee::getTotalAmountPaid() const {
    return totalAmountPaid;
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

void Employee::setJobPosition(QString position) {
    jobPosition = position;
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


void Employee::setNumberOfHours(int hours) {
    numberOfHours = hours;
}


void Employee::setTotalNumberOfHours(int hours) {
    totalNumberOfHours = hours;
}

void Employee::setNumberOfOvertimeHours(int hours) {
    numberOfOvertimeHours = hours;
}


void Employee::setTotalNumberOfOvertimeHours(int hours) {
    totalNumberOfOvertimeHours = hours;
}

void Employee::setHourlyWage(double wage) {
    hourlyWage = wage;
}

double Employee::calcPay() const {
    return hourlyWage * (numberOfHours + numberOfOvertimeHours);
}


void Employee::setTotalAmountPaid(double amount) {
    totalAmountPaid = amount;
}
