#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAuthor_triggered()
{
    QLabel *author = new QLabel();
    author->setWindowFlags(Qt::Window);
    author->setText("THIS WAS WRITTEN BY CALVIN");
    author->setAttribute(Qt::WA_DeleteOnClose);
    author->show();
}

void MainWindow::on_addButton_clicked()
{
    QString employeeId = "E" + QString::number(id);
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString gender = ui->genderComboBox->currentText();
    QString jobPosition = ui->jobPositionLineEdit->text();
    QString streetAddress = ui->streetAddressLineEdit->text();
    QString city = ui->cityLineEdit->text();
    QString state = ui->stateLineEdit->text();
    QString zipcode = ui->zipcodeLineEdit->text();
    double hourlyWage = ui->hourlyWageLineEdit->text().toDouble();
    int numberOfHours = ui->numberOfHoursWorkedLineEdit->text().toInt();

    ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
    id++;

    refreshList();
    clearForms();
}

void MainWindow::on_employeeListView_clicked(const QModelIndex &index)
{
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QStringList employeeInfo = employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    Employee employee = ps->getEmployeeById(employeeInfo[0]);
    ui->firstNameLineEdit->setText(employee.getFirstName());
    ui->lastNameLineEdit->setText(employee.getLastName());
    ui->genderComboBox->setCurrentText(employee.getGender());
    ui->jobPositionLineEdit->setText(employee.getJobPosition());
    ui->streetAddressLineEdit->setText(employee.getStreetAddress());
    ui->cityLineEdit->setText(employee.getCity());
    ui->stateLineEdit->setText(employee.getState());
    ui->zipcodeLineEdit->setText(employee.getZipcode());
    ui->hourlyWageLineEdit->setText(QString::number(employee.getHourlyWage()));
    ui->numberOfHoursWorkedLineEdit->setText(QString::number(employee.getNumberOfHours()));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    refreshList();
}

void MainWindow::setUpValidators() const {
    // You can try QDoubleValidator and QIntValidator
    QRegExpValidator* integerValidator = new QRegExpValidator(QRegExp("\\d*"));
    QRegExpValidator* doubleValidator = new QRegExpValidator(QRegExp("\\d*\\.?\\d"));
    QRegExpValidator* zipcodeValidator = new QRegExpValidator(QRegExp("^[0-9]{5}(?:-[0-9]{4})?$"));
    ui->hourlyWageLineEdit->setValidator(doubleValidator);
    ui->numberOfHoursWorkedLineEdit->setValidator(integerValidator);
    ui->zipcodeLineEdit->setValidator(zipcodeValidator);
}

void MainWindow::refreshOverview() {

}

void MainWindow::refreshList() {
    QStringListModel *model = new QStringListModel();
    QStringList list = ps->getStringListOfEmployees();
    model->setStringList(list);
    ui->employeeListView->setModel(model);
}

void MainWindow::clearForms() {
    // Clear forms
    foreach(QLineEdit* le, this->findChildren<QLineEdit*>()) {
        le->clear();
    }
}

void MainWindow::on_removeButton_clicked()
{
    if (ui->employeeListView->currentIndex().isValid() == false) {
        return;
    }
    const QModelIndex &index = ui->employeeListView->currentIndex();
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QStringList employeeInfo = employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    ps->removeEmployeeById(employeeInfo[0]);

    refreshList();
    clearForms();
}

void MainWindow::on_editButton_clicked()
{
    QString employeeId = "E" + QString::number(id);
    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString gender = ui->genderComboBox->currentText();
    QString jobPosition = ui->jobPositionLineEdit->text();
    QString streetAddress = ui->streetAddressLineEdit->text();
    QString city = ui->cityLineEdit->text();
    QString state = ui->stateLineEdit->text();
    QString zipcode = ui->zipcodeLineEdit->text();
    double hourlyWage = ui->hourlyWageLineEdit->text().toDouble();
    int numberOfHours = ui->numberOfHoursWorkedLineEdit->text().toInt();

    ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
}
