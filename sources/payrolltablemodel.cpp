#include "headers/payrolltablemodel.h"

PayrollTableModel::PayrollTableModel(vector<Employee> list, QObject *parent): QStandardItemModel(parent), payrollList(list) {
    setUpModel();
}

int PayrollTableModel::rowCount(const QModelIndex &parent) const {
    return payrollList.size();
}

int PayrollTableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

void PayrollTableModel::setUpModel() {
    const int ROWS = (int) payrollList.size();
    const int COLUMNS = 4;
    this->setRowCount(ROWS);
    this->setColumnCount(COLUMNS);
    setHeaderData(0, Qt::Horizontal, QObject::tr("Employee ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Amount To Be Paid ($)"));

    for (int row = 0; row < ROWS; row++) {
        Employee e = payrollList[row];
        Paycheck p = Paycheck(e.getEmployeeId(), e.getFirstName(), e.getLastName(), e.calcPay());
        for (int col = 0; col < COLUMNS; col++) {
            QModelIndex index = this->index(row,col,QModelIndex());
            switch(col) {
                case 0:
                    setData(index, p.getEmployeeId());
                    break;
                case 1:
                    setData(index, p.getFirstName());
                    break;
                case 2:
                    setData(index, p.getLastName());
                    break;
                case 3:
                    setData(index, p.getPayCheckAmount());
                    break;
                default:
                    break;
            }
        }
    }
}
