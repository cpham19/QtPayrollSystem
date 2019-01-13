#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshOverview();
    void refreshList();
    void clearForms();
    void setUpValidators() const;

private slots:
    void on_actionAuthor_triggered();
    void on_addButton_clicked();
    void on_employeeListView_clicked(const QModelIndex &index);
    void on_tabWidget_currentChanged(int index);
    void on_removeButton_clicked();
    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
