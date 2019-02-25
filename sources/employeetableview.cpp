#include "headers/employeetableview.h"

EmployeeTableView::EmployeeTableView(PayrollSystem *ps, QWidget *parent): QTableView(parent) {
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->verticalHeader()->setDefaultSectionSize(50);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSortingEnabled(true);
    tableViewModel = new EmployeeTableModel(ps);
    setModel(tableViewModel);
}


