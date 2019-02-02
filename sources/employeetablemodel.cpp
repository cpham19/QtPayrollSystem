#include "headers/employeetablemodel.h"

EmployeeTableModel::EmployeeTableModel(PayrollSystem *payrollSystem, QObject *parent): QStandardItemModel(parent), ps(payrollSystem) {
    setUpModel();
}

//int EmployeeTableModel::rowCount(const QModelIndex &parent) const {
//    return ps->getPayrollList().size();
//}

int EmployeeTableModel::columnCount(const QModelIndex &parent) const {
    return 12;
}

void EmployeeTableModel::setUpModel() {
    int ROWS = ps->getPayrollList().size();
    int COLUMNS = 12;

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
    setHeaderData(11, Qt::Horizontal, QObject::tr("Amount to be Paid ($)"));

    for (int row = 0; row < ROWS; row++) {
        Employee e = ps->getPayrollList()[row];
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
                case 11:
                    setData(index, e.calcPay());
                    break;
                default:
                    break;
            }
        }
    }
}

void EmployeeTableModel::removeRowByRow(QString employeeId, int row) {
    ps->removeEmployeeById(employeeId);

    removeRow(row);
}

void EmployeeTableModel::insertNewRow(QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours) {
    ps->addEmployee(employeeId, firstName, lastName, gender, position, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

    QStandardItem* employeeIdCol = new QStandardItem(employeeId);
    QStandardItem* firstNameCol = new QStandardItem(firstName);
    QStandardItem* lastNameCol = new QStandardItem(lastName);
    QStandardItem* genderCol = new QStandardItem(gender);
    QStandardItem* positionCol = new QStandardItem(position);
    QStandardItem* streetCol = new QStandardItem(streetAddress);
    QStandardItem* cityCol = new QStandardItem(city);
    QStandardItem* stateCol = new QStandardItem(state);
    QStandardItem* zipcodeCol = new QStandardItem(zipcode);
    QStandardItem* wageCol = new QStandardItem(QString::number(hourlyWage));
    QStandardItem* hoursCol = new QStandardItem(QString::number(numberOfHours));
    QStandardItem* amountCol = new QStandardItem(QString::number(hourlyWage * numberOfHours));

    QList<QStandardItem*> newRow;
    newRow.append(employeeIdCol);
    newRow.append(firstNameCol);
    newRow.append(lastNameCol);
    newRow.append(genderCol);
    newRow.append(positionCol);
    newRow.append(streetCol);
    newRow.append(cityCol);
    newRow.append(stateCol);
    newRow.append(zipcodeCol);
    newRow.append(wageCol);
    newRow.append(hoursCol);
    newRow.append(amountCol);

    appendRow(newRow);
}

void EmployeeTableModel::editRow(int row, QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours) {
    ps->editEmployee(employeeId, firstName, lastName, gender, position, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

    for (int col = 1; col < 12; col++) {
        QModelIndex index = this->index(row,col,QModelIndex());
        switch(col) {
            case 1:
                setData(index, firstName);
                break;
            case 2:
                setData(index, lastName);
                break;
            case 3:
                setData(index, gender);
                break;
            case 4:
                setData(index, position);
                break;
            case 5:
                setData(index, streetAddress);
                break;
            case 6:
                setData(index, city);
                break;
            case 7:
                setData(index, state);
                break;
            case 8:
                setData(index, zipcode);
                break;
            case 9:
                setData(index, hourlyWage);
                break;
            case 10:
                setData(index, numberOfHours);
                break;
            case 11:
                setData(index, QString::number(hourlyWage * numberOfHours));
                break;
            default:
                break;
        }
    }
}
