#ifndef EMPLOYEESTRINGLISTMODEL_H
#define EMPLOYEESTRINGLISTMODEL_H

#include <QStringListModel>
#include <QStringList>
#include <QObject>


class EmployeeStringListModel : public QStringListModel
{
    Q_OBJECT
public:
    EmployeeStringListModel(const QStringList &list, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

private:
    QStringList stringList;
};

#endif // EMPLOYEESTRINGLISTMODEL_H
