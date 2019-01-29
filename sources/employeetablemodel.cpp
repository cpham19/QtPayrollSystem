#include "headers/employeetablemodel.h"

EmployeeTableModel::EmployeeTableModel(vector<Employee> list, QObject *parent): QStandardItemModel(parent), payrollList(list) {
    setUpModel();
}

int EmployeeTableModel::rowCount(const QModelIndex &parent) const {
    return payrollList.size();
}

int EmployeeTableModel::columnCount(const QModelIndex &parent) const {
    return 11;
}

void EmployeeTableModel::setUpModel() {
    int ROWS = payrollList.size();
    int COLUMNS = 11;

    this->setRowCount(ROWS);
    this->setColumnCount(COLUMNS);
    setHeaderData(0, Qt::Horizontal, QObject::tr("Employee ID"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    setHeaderData(3, Qt::Horizontal, QObject::tr("Gender"));
    setHeaderData(4, Qt::Horizontal, QObject::tr("Job Position"));
    setHeaderData(5, Qt::Horizontal, QObject::tr("Street Address"));
    setHeaderData(6, Qt::Horizontal, QObject::tr("City"));
    setHeaderData(7, Qt::Horizontal, QObject::tr("State"));
    setHeaderData(8, Qt::Horizontal, QObject::tr("Zipcode"));
    setHeaderData(9, Qt::Horizontal, QObject::tr("Hourly Wage"));
    setHeaderData(10, Qt::Horizontal, QObject::tr("Hours Worked"));

    for (int row = 0; row < ROWS; row++) {
        Employee e = payrollList[row];
        for (int col = 0; col < COLUMNS; col++) {
            QModelIndex index = this->index(row,col,QModelIndex());
            switch(col) {
                case 0:
                    setData(index, e.getEmployeeId());
                    break;
                case 1:
                    setData(index, e.getFirstName());
                    break;
                case 2:
                    setData(index, e.getLastName());
                    break;
                case 3:
                    setData(index, e.getGender());
                    break;
                case 4:
                    setData(index, e.getJobPosition());
                    break;
                case 5:
                    setData(index, e.getStreetAddress());
                    break;
                case 6:
                    setData(index, e.getCity());
                    break;
                case 7:
                    setData(index, e.getState());
                    break;
                case 8:
                    setData(index, e.getZipcode());
                    break;
                case 9:
                    setData(index, e.getHourlyWage());
                    break;
                case 10:
                    setData(index, e.getNumberOfHours());
                    break;
                default:
                    break;
            }
        }
    }

}
