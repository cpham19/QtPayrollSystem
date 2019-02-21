#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
using namespace std;

class Employee {
    public:
        Employee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, double wage, int hours, double totalAmountPaid, int totalNumberOfHours);
        QString getEmployeeId() const;
        QString getFirstName() const;
        QString getLastName() const;
        QString getGender() const;
        QString getJobPosition() const;
        QString getStreetAddress() const;
        QString getCity() const;
        QString getState() const;
        QString getZipcode() const;
        double getHourlyWage() const;
        int getNumberOfHours() const;
        int getTotalNumberOfHours() const;
        double getTotalAmountPaid() const;
        void setFirstName(QString fName);
        void setLastName(QString lName);
        void setGender(QString gender);
        void setJobPosition(QString position);
        void setStreetAddress(QString address);
        void setCity(QString city);
        void setState(QString state);
        void setZipcode(QString zipcode);
        void setHourlyWage(double wage);
        void setNumberOfHours(int hours);
        void setTotalNumberOfHours(int hours);
        void setTotalAmountPaid(double amount);
        double calcPay() const;

    private:
        QString employeeId;
        QString firstName;
        QString lastName;
        QString gender;
        QString jobPosition;
        QString streetAddress;
        QString city;
        QString state;
        QString zipcode;
        double hourlyWage;
        int numberOfHours;
        int totalNumberOfHours;
        double totalAmountPaid;
};

#endif
