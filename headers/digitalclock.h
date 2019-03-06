#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QMessageBox>
#include <QLCDNumber>
#include <QtWidgets>
#include <iostream>
#include <random>
#include "payrollsystem.h"
#include "employeetableview.h"

using namespace std;

class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigitalClock(QPushButton *timerButton, QLabel *datelabel, QLabel *meridiemLabel, PayrollSystem *payrollSystem, EmployeeTableView *employeeTableView, QWidget *parent = nullptr);
    void generateRandomDateAndTime();
    QString getDateString() const;
    void stopTimer();
    void startTimer();

    PayrollSystem *ps;
    EmployeeTableView *employeeTableView;
    QTimer *timer;
    QPushButton *timerButton;
    QLabel *dateLabel;
    QLabel *meridiemLabel;

    QString meridiem;
    int day;
    int month;
    int year;

    int hour;
    int minute;

private slots:
    void showTime();

private:
    int timerId;
};


#endif // DIGITALCLOCK_H
