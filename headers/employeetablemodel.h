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
    void insertNewRow(QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours);
    void removeRowByRow(QString employeeId, int row);
    void editRow(int row, QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours);
    void payAllRows();
    void incrementHours();


private:
    PayrollSystem *ps;
};

#endif // EMPLOYEETABLEMODEL_H
