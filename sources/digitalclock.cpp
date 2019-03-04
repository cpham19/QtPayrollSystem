#include "headers/digitalclock.h"
#include "headers/globals.h"

DigitalClock::DigitalClock(QLabel *dl, QLabel *ml, PayrollSystem *payrollSystem, EmployeeTableView *tv, QWidget *parent) : dateLabel(dl), meridiemLabel(ml), ps(payrollSystem), employeeTableView(tv), QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(100);

    generateRandomDateAndTime();
    showTime();

    setWindowTitle(tr("Digital Clock"));
    resize(50, 50);
}

void DigitalClock::stopTimer() {
    timer->stop();
}

void DigitalClock::startTimer() {
    timer->start();
}

void DigitalClock::generateRandomDateAndTime() {
    mt19937 generator(rand());

    uniform_int_distribution<int> monthsDistribution(0, months.size() - 1);
    uniform_int_distribution<int> yearsDistribution(2000, 2020);

    month = months[monthsDistribution(generator)];
    uniform_int_distribution<int> daysDistribution(1, days[month]);
    day = daysDistribution(generator);
    year = yearsDistribution(generator);

    // Each distribution has a different size for each text file
    uniform_int_distribution<int> hoursDistribution(0, hours.size() - 1);
    //uniform_int_distribution<int> minutesDistribution(0, minutes.size() - 1);
    uniform_int_distribution<int> meridiemsDistribution(0, meridiems.size() - 1);

    hour = hours[hoursDistribution(generator)];
    minute = 0;
    meridiem = meridiems[meridiemsDistribution(generator)];
    //minute = minutes[minutesDistribution(generator)];
}

QString DigitalClock::getDateString() const {
    return monthStrings[month] + " " + QString::number(day) + ", " + QString::number(year);
}

void DigitalClock::showTime()
{
    if (minute == 59) {
        minute = 0;
        hour++;
        if (hour == 12 && meridiem.compare("AM") == 0) {
            meridiem = "PM";
        }
        else if (hour == 12 && meridiem.compare("PM") == 0) {
            meridiem = "AM";
            day++;
        }
        else if (hour == 13) {
            hour = 1;
        }

        ps->incrementHoursOfEmployees();
        employeeTableView->tableViewModel->incrementHours();

        if (day == days[month]) {
            day = 1;

            if (month == 12) {
                month = 1;
                year++;
            }
            else {
                month++;
            }
        }
    }
    else {
        minute++;
    }

    QString timeText;
    if (minute <= 9) {
        timeText = QString::number(hour) + ":0" + QString::number(minute);
    }
    else {
        timeText = QString::number(hour) + ":" + QString::number(minute);
    }

    dateLabel->setText(getDateString());
    meridiemLabel->setText(meridiem);
    display(timeText);
}
