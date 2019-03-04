#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee {
    public:
        Employee(QString id, QString fName, QString lName, QString gender, QString position, QString address, QString city, QString state, QString zipcode, int hours, int totalNumberOfHours, int overtimeHours, int totalNumberOfOvertimeHours, double wage, double amountToBePaid, double totalAmountPaid);
        QString getEmployeeId() const;
        QString getFirstName() const;
        QString getLastName() const;
        QString getGender() const;
        QString getJobPosition() const;
        QString getStreetAddress() const;
        QString getCity() const;
        QString getState() const;
        QString getZipcode() const;
        int getNumberOfHours() const;
        int getTotalNumberOfHours() const;
        int getNumberOfOvertimeHours() const;
        int getTotalNumberOfOvertimeHours() const;
        double getHourlyWage() const;
        double getAmountToBePaid() const;
        double getTotalAmountPaid() const;
        void setFirstName(QString fName);
        void setLastName(QString lName);
        void setGender(QString gender);
        void setJobPosition(QString position);
        void setStreetAddress(QString address);
        void setCity(QString city);
        void setState(QString state);
        void setZipcode(QString zipcode);
        void setNumberOfHours(int hours);
        void setTotalNumberOfHours(int hours);
        void setNumberOfOvertimeHours(int hours);
        void setAmountToBePaid(double amount);
        void setTotalNumberOfOvertimeHours(int hours);
        void setHourlyWage(double wage);
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
        int numberOfHours;
        int totalNumberOfHours;
        int numberOfOvertimeHours;
        int totalNumberOfOvertimeHours;
        double hourlyWage;
        double amountToBePaid;
        double totalAmountPaid;
};

#endif
