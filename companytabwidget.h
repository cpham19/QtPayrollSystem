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
#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include "payrollsystem.h"
#include <cmath>
#include <random>

class CompanyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    CompanyTabWidget(QWidget *parent = nullptr, QString name = "");
    ~CompanyTabWidget();
    void initializeData(QString name);
    void createOverviewTab();
    void createEmployeeTab();
    void createEmployeeTableTab();
    void createPayrollTab();
    void setUpValidators();
    void setUpEmployeeListView();
    void setUpEmployeeInputs();
    void setUpEmployeeTable();
    void setUpPayrollTable();
    void update();

    // Overview Tab
    QGroupBox *overviewGroupBox;
    QGridLayout *overviewLayout;
    QLabel *nameOfCompanyLabel;
    QLabel *numberOfEmployeesLabel;
    QLabel *totalAmountPaidLabel;

    // Employee Tab
    QGroupBox *employeeGroupBox;
    QGridLayout *employeeLayout;
    QLineEdit *firstNameLineEdit;
    QLineEdit *lastNameLineEdit;
    QComboBox *genderComboBox;
    QLineEdit *jobPositionLineEdit;
    QLineEdit *streetAddressLineEdit;
    QLineEdit *cityLineEdit;
    QLineEdit *stateLineEdit;
    QLineEdit *zipcodeLineEdit;
    QLineEdit *hourlyWageLineEdit;
    QLineEdit *numberOfHoursLineEdit;

    QListView *employeeListView;
    QStringListModel *listViewModel;
    QStringList listOfListViewModel;

    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *clearButton;

    // Employee Table Tab
    QGroupBox *tableGroupBox;
    QTableView *employeeTableView;
    QStandardItemModel *tableViewModel;

    // Payroll Tab
    QGroupBox *payrollGroupBox;
    QTableView *payrollTableView;
    QStandardItemModel *payrollViewModel;
    QPushButton *payButton;

    PayrollSystem *ps;
    int id;

signals:

public slots:

private slots:
    void addEmployee();
    void editEmployee();
    void removeEmployee();
    void payEmployees();
    void tabChanged(int index);
    void employeeListViewClicked(const QModelIndex &index);
    void clearForms();

private:

};

#endif // COMPANYTABWIDGET_H
