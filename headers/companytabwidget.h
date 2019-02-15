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

#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>

#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>

#include "payrollsystem.h"
#include "employeetablemodel.h"
#include <cmath>
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
    void createOutputTab();

    void createTimer();
    void stopTimer();

    void setUpValidators();
    void setUpEmployeeInputs();
    void setUpEmployeeTable();

    void update();
    void addEmployeeByQStringList(QStringList list);

    QString getCurrentTimeStamp() const;

    // Overview Tab
    QGroupBox *overviewGroupBox;
    QGridLayout *overviewLayout;
    QLabel *nameOfCompanyLabel;
    QLabel *numberOfEmployeesLabel;
    QLabel *totalAmountPaidLabel;

    // Employee Table Tab
    QGroupBox *tableGroupBox;
    QGridLayout *tableLayout;
    QTableView *employeeTableView;
    EmployeeTableModel *tableViewModel;

    // Dialog
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
    QLabel *genderComboBoxLabel;
    QComboBox *genderComboBox;
    QLabel *jobPositionLabel;
    QComboBox *jobPositionComboBox;
    QLabel *streetAddressLabel;
    QLineEdit *streetAddressLineEdit;
    QLabel *cityLabel;
    QComboBox *cityComboBox;
    QLabel *stateLabel;
    QComboBox *stateComboBox;
    QLabel *zipcodeLabel;
    QLineEdit *zipcodeLineEdit;
    QLabel *hourlyWageLabel;
    QLineEdit *hourlyWageLineEdit;
    QLabel *numberOfHoursLabel;
    QLineEdit *numberOfHoursLineEdit;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *generateEmployeesButton;
    QPushButton *payAllButton;

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
    void automaticallyFill();
    void saveToFile();

private:
    int timerId;

protected:
    void timerEvent(QTimerEvent *event);

};

#endif // COMPANYTABWIDGET_H
