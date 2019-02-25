#include "headers/employeetablemodel.h"

EmployeeTableModel::EmployeeTableModel(PayrollSystem *payrollSystem, QObject *parent): QStandardItemModel(parent), ps(payrollSystem) {
    setUpModel();
}

//int EmployeeTableModel::rowCount(const QModelIndex &parent) const {
//    return ps->getPayrollList().size();
//}

int EmployeeTableModel::columnCount(const QModelIndex &parent) const {
    return 14;
}

void EmployeeTableModel::setUpModel() {
    int ROWS = ps->getPayrollList().size();
    int COLUMNS = 14;

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
    setHeaderData(12, Qt::Horizontal, QObject::tr("Total Amount of Hours"));
    setHeaderData(13, Qt::Horizontal, QObject::tr("Total Amount Paid ($)"));

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
                setData(index, QString::number(e.calcPay(), 'f', 2));
                break;
            case 12:
                setData(index, QString::number(e.getTotalNumberOfHours()));
                break;
            case 13:
                setData(index, QString::number(e.getTotalAmountPaid(), 'f', 2));
                break;
            default:
                break;
            }
        }
    }
}

void EmployeeTableModel::removeRowByRow(QString employeeId, int row) {
    removeRow(row);
}

void EmployeeTableModel::insertNewRow(QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours, double totalAmountPaid, int totalNumberOfHours) {
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
    QStandardItem* amountCol = new QStandardItem(QString::number(hourlyWage * numberOfHours, 'f', 2));
    QStandardItem* totalNumberOfHoursCol = new QStandardItem(QString::number(totalNumberOfHours));
    QStandardItem* totalAmountPaidCol = new QStandardItem(QString::number(totalAmountPaid, 'f', 2));

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
    newRow.append(totalNumberOfHoursCol);
    newRow.append(totalAmountPaidCol);

    appendRow(newRow);
}

void EmployeeTableModel::editRow(int row, QString employeeId, QString firstName, QString lastName, QString gender, QString position, QString streetAddress, QString city, QString state, QString zipcode, double hourlyWage, int numberOfHours) {
    for (int col = 1; col < 14; col++) {
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
            setData(index, QString::number(hourlyWage * numberOfHours, 'f', 2));
            break;
        default:
            break;
        }
    }
}

void EmployeeTableModel::payAllRows() {
    for (int row = 0; row < ps->getPayrollList().size(); row++) {
        for (int col = 10; col < 14; col++) {
            QModelIndex index = this->index(row,col,QModelIndex());
            switch(col) {
            case 10:
                setData(index, QString::number(0));
                break;
            case 11:
                setData(index, QString::number(0.00, 'f', 2));
                break;
            case 12:
                setData(index, QString::number(ps->getPayrollList()[row].getTotalNumberOfHours()));
                break;
            case 13:
                setData(index, QString::number(ps->getPayrollList()[row].getTotalAmountPaid(), 'f', 2));
                break;
            default:
                break;
            }
        }
    }
}

void EmployeeTableModel::incrementHours() {
    for (int row = 0; row < ps->getPayrollList().size(); row++) {
        Employee e = ps->getPayrollList()[row];
        for (int col = 10; col < 14; col++) {
            QModelIndex index = this->index(row,col,QModelIndex());
            switch(col) {
            case 10:
                setData(index, QString::number(e.getNumberOfHours()));
                break;
            case 11:
                setData(index, QString::number(e.getNumberOfHours() * e.getHourlyWage(), 'f', 2));
                break;
            default:
                break;
            }
        }
    }
}
