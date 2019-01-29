#ifndef PAYROLLTABLEMODEL_H
#define PAYROLLTABLEMODEL_H

#include <QStandardItemModel>
#include "headers/employee.h"
#include "headers/payrollsystem.h"

class PayrollTableModel : public QStandardItemModel
{
    Q_OBJECT

public:
    PayrollTableModel(vector<Employee> list, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void setUpModel();


private:
    vector<Employee> payrollList;
};

#endif // PAYROLLTABLEMODEL_H
