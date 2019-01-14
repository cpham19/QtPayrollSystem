#ifndef COMPANYTABWIDGET_H
#define COMPANYTABWIDGET_H

#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QListView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QPushButton>
#include <QModelIndex>
#include "payrollsystem.h"

class CompanyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    CompanyTabWidget(QWidget *parent = nullptr);
    void initialize();
    void createOverviewTab();
    void createEmployeeTab();
    void setUpValidators();
    void refreshEmployeeListView();
    void clearForms();

    QGroupBox *overviewGroupBox;
    QGroupBox *employeeGroupBox;

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

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    PayrollSystem *ps;
    int id;

signals:

public slots:

private slots:
    void addEmployee();
    void editEmployee();
    void removeEmployee();
    void tabChanged(int index);
    void employeeListViewClicked(const QModelIndex &index);

private:

};

#endif // COMPANYTABWIDGET_H
