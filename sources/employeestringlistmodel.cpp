#include "headers/employeestringlistmodel.h"

// http://www.java2s.com/Code/Cpp/Qt/stringlistmodelexample.htm

EmployeeStringListModel::EmployeeStringListModel(const QStringList &list, QObject *parent): QStringListModel(parent), stringList(list) {

}

int EmployeeStringListModel::rowCount(const QModelIndex &parent) const {
    return stringList.count();
}

/*!
    Returns an appropriate value for the requested data.
    If the view requests an invalid index, an invalid variant is returned.
    Any valid index that corresponds to a string in the list causes that
    string to be returned.
*/
QVariant EmployeeStringListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= stringList.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return stringList.at(index.row());
    }
    else {
        return QVariant();
    }
}

/*!
    Returns an appropriate value for the item's flags. Valid items are
    enabled, selectable, and editable.
*/
Qt::ItemFlags EmployeeStringListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


/*!
    Changes an item in the string list, but only if the following conditions
    are met:

    * The index supplied is valid.
    * The index corresponds to an item to be shown in a view.
    * The role associated with editing text is specified.

    The dataChanged() signal is emitted if the item is changed.
*/
bool EmployeeStringListModel::setData(const QModelIndex &index,
                              const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
}


/*!
    Inserts a number of rows into the model at the specified position.
*/
bool EmployeeStringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.insert(position, "");
    }

    endInsertRows();
    return true;

}


/*!
    Removes a number of rows from the model at the specified position.
*/
bool EmployeeStringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }

    endRemoveRows();
    return true;

}
