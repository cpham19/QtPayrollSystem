#ifndef BUDGETDIALOG_H
#define BUDGETDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>

class BudgetDialog : public QDialog
{
    Q_OBJECT

public:
    BudgetDialog(QWidget *parent = nullptr);
    void setupInputs();
    void setupValidators();

    QLineEdit *budgetLineEdit;

signals:
    //void rejected();
    //void accepted();

public slots:


private:
    QLineEdit * le;
};

#endif // BUDGETDIALOG_H
