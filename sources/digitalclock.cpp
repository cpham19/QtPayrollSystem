#include "headers/digitalclock.h"
#include "headers/globals.h"

DigitalClock::DigitalClock(QPushButton *tb, QLabel *dl, QLabel *ml, PayrollSystem *payrollSystem, EmployeeTableView *tv, QWidget *parent) : timerButton(tb), dateLabel(dl), meridiemLabel(ml), ps(payrollSystem), employeeTableView(tv), QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1);
    timer->stop();

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

    //uniform_int_distribution<int> daysDistribution(1, days[month]);
    //day = daysDistribution(generator);
    day = 1;
    year = yearsDistribution(generator);;

    // Each distribution has a different size for each text file
    uniform_int_distribution<int> hoursDistribution(0, hours.size() - 1);
    //uniform_int_distribution<int> minutesDistribution(0, minutes.size() - 1);
    uniform_int_distribution<int> meridiemsDistribution(0, meridiems.size() - 1);

    hour = 9;
    minute = 0;
    meridiem = "AM";

    //hour = hours[hoursDistribution(generator)];
    //meridiem = meridiems[meridiemsDistribution(generator)];
    //minute = minutes[minutesDistribution(generator)];
}

QString DigitalClock::getDateString() const {
    return monthStrings[month - 1] + " " + QString::number(day) + ", " + QString::number(year);
}

void DigitalClock::showTime()
{
    // Last minute of the hour
    if (minute == 59) {
        minute = 0;
        hour++;
        if (hour == 12 && meridiem.compare("AM") == 0) {
            meridiem = "PM";
        }
        // Change the meridiem to AM after becoming 12
        else if (hour == 12 && meridiem.compare("PM") == 0) {
            meridiem = "AM";

            // The last day of the month
            // vector<int> months{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
            // vector<int> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            // vector<int> hours{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

            // if month = 12, then months[month -1] = 12, then days[months[month- 1] - 1] = 31
            // if month = 1, then months[month - 1] = 1, then days[months[month - 1] -1 ] = 1
            if (day == days[months[month - 1] - 1]) {
                day = 1;

                if (month == 12) {
                    month = 1;
                    year++;
                }
                else {
                    month++;
                }

                stopTimer();
                timerButton->setText("Start Timer");
                ps->issuePaychecks();
                employeeTableView->tableViewModel->payAllRows();
            }
            else {
                day++;
            }
        }
        else if (hour == 13) {
            hour = 1;
        }

        ps->incrementHoursOfEmployees(QString::number(hour) + " " + meridiem);
        employeeTableView->tableViewModel->incrementHours();
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
