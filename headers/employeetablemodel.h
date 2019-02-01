#ifndef EMPLOYEETABLEMODEL_H
#define EMPLOYEETABLEMODEL_H

#include <QStandardItemModel>
#include "headers/employee.h"
#include "headers/payrollsystem.h"

class EmployeeTableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    EmployeeTableModel(vector<Employee> &list, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void setUpModel();


private:
    vector<Employee> payrollList;
};

#endif // EMPLOYEETABLEMODEL_H
