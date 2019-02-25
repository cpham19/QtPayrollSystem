#ifndef CustomDialog_H
#define CustomDialog_H

#include <QFormLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include <cmath>
#include <random>

class CustomDialog : public QDialog
{
    Q_OBJECT
public:
    CustomDialog(QWidget *parent = nullptr);
    void setUpInputs();
    void setUpValidators();

    // Dialog
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
    QLabel *genderComboBoxLabel;
    QComboBox *genderComboBox;
    QLabel *jobPositionLabel;
    QComboBox *jobPositionComboBox;
    QLabel *streetAddressLabel;
    QLineEdit *streetAddressLineEdit;
    QLabel *cityLabel;
    QComboBox *cityComboBox;
    QLabel *stateLabel;
    QComboBox *stateComboBox;
    QLabel *zipcodeLabel;
    QLineEdit *zipcodeLineEdit;
    QLabel *hourlyWageLabel;
    QLineEdit *hourlyWageLineEdit;
    QLabel *numberOfHoursLabel;
    QLineEdit *numberOfHoursLineEdit;

signals:

private slots:
    void automaticallyFill();

private:

};

#endif // CustomDialog_H
