#ifndef EMPLOYEETABLEVIEW_H
#define EMPLOYEETABLEVIEW_H

#include <QTableView>
#include <QHeaderView>
#include "employeetablemodel.h"

class EmployeeTableView : public QTableView
{
    Q_OBJECT

public:
    EmployeeTableView(PayrollSystem *payrollSystem, QWidget *parent = nullptr);
    EmployeeTableModel *tableViewModel;


private:

};

#endif // EMPLOYEETABLEVIEW_H
