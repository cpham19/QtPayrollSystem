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

class CompanyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    CompanyTabWidget(QWidget *parent = nullptr, QString name = "");
    ~CompanyTabWidget();
    void initializeData(QString name);
    void createOverviewTab();
    void createEmployeeTableTab();
    void setUpValidators();
    void setUpEmployeeInputs();
    void setUpEmployeeTable();
    void update();
    QString getCurrentTimeStamp() const;

    // Overview Tab
    QGroupBox *overviewGroupBox;
    QGridLayout *overviewLayout;
    QLabel *nameOfCompanyLabel;
    QLabel *numberOfEmployeesLabel;
    QLabel *totalAmountPaidLabel;

    // Employee Table Tab
    QGroupBox *tableGroupBox;
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
    QLineEdit *jobPositionLineEdit;
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
    QPushButton *payAllButton;

    PayrollSystem *ps;
    int id;

signals:

public slots:

private slots:
    void toggleAddDialog();
    void toggleEditDialog();
    void removeEmployee();
    void payAllEmployees();
    void tabChanged(int index);
    void automaticallyFill();

private:
    int timerId;

protected:
    void timerEvent(QTimerEvent *event);

};

#endif // COMPANYTABWIDGET_H
