#include "headers/budgetdialog.h"

BudgetDialog::BudgetDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Edit Budget");
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    setupInputs();
    setupValidators();
}

// Used for creating the form itself
void BudgetDialog::setupInputs() {
    // Use a layout allowing to have a label next to each field
    QFormLayout *form = new QFormLayout(this);

    QLabel *budgetLabel = new QLabel();
    budgetLabel->setText("Current Budget: $");

    budgetLineEdit = new QLineEdit();
    form->addRow(budgetLabel, budgetLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, this);

    form->addRow(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

// Used for data input validation
void BudgetDialog::setupValidators() {
    // You can try QDoubleValidator and QIntValidator
    QRegExpValidator* doubleValidator = new QRegExpValidator(QRegExp("\\d*\\.?\\d\\d"));
    budgetLineEdit->setValidator(doubleValidator);
}
