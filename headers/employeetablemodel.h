#ifndef EMPLOYEETABLEMODEL_H
#define EMPLOYEETABLEMODEL_H

#include <QStandardItemModel>
#include "headers/employee.h"
#include "headers/payrollsystem.h"

class EmployeeTableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    EmployeeTableModel(PayrollSystem *payrollSystem, QObject *parent = nullptr);
    //int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void setUpModel();
    void insertNewRow(QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, int hours, int totalNumberOfHours, int overtimeHours, int totalNumberOfOvertimeHours, double wage, double amountToBePaid, double totalAmountPaid);
    void removeRowByRow(int row);
    void payRowByRow(int row);
    void editRow(int row, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, int numberOfHours, double hourlyWage);
    void payAllRows();
    void incrementHours();


private:
    PayrollSystem *ps;
};

#endif // EMPLOYEETABLEMODEL_H
