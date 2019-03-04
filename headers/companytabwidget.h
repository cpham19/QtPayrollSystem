#ifndef COMPANYTABWIDGET_H
#define COMPANYTABWIDGET_H

#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QPushButton>
#include <QModelIndex>
#include <QApplication>

#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>

#include <QJsonObject>
#include <QColor>
#include <QAbstractBarSeries>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>

#include "payrollsystem.h"
#include "statisticslayout.h"
#include "employeetableview.h"
#include "customdialog.h"
#include "globals.h"
#include "digitalclock.h"

#include <random>

#include <QDateTime>
#include <QFile>

class CompanyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    CompanyTabWidget(QWidget *parent = nullptr, QString name = "");
    ~CompanyTabWidget();
    void initializeData(QString name);

    void createOverviewTab();
    void createEmployeeTableTab();
    void createStatisticsTab();
    void createOutputTab();

    void startTimer();
    void stopTimer();

    void update();
    void addEmployeeByQStringList(QStringList list);

    QString getCurrentTimeStamp() const;

    // Overview Tab
    QGroupBox *overviewGroupBox;
    QGridLayout *overviewLayout;
    QLabel *nameOfCompanyLabel;
    QLabel *nameOfCEOLabel;
    QLabel *numberOfEmployeesLabel;
    QLabel *totalAmountPaidLabel;

    // Employee Table Tab
    QGroupBox *tableGroupBox;
    QGridLayout *tableLayout;
    QLabel *dateLabel;
    DigitalClock *clock;
    QLabel *meridiemLabel;
    EmployeeTableView *employeeTableView;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *generateEmployeesButton;
    QPushButton *payAllButton;
    QPushButton *timerButton;

    // Statistics Tab
    QGroupBox *statsGroupBox;
    QStackedWidget *stackedWidget;
    StatisticsLayout *statsLayout;

    PayrollSystem *ps;
    int id;

    // Output Tab
    QGroupBox *outputGroupBox;
    QGridLayout *outputLayout;
    QPushButton *saveToFileButton;

signals:

public slots:

private slots:
    void toggleAddDialog();
    void toggleEditDialog();
    void removeEmployee();
    void generateRandomEmployees();
    void payAllEmployees();
    void tabChanged(int index);
    void saveToFile();
    void toggleTimerButton();

protected:

};

#endif // COMPANYTABWIDGET_H
