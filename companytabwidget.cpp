#include "companytabwidget.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent): QTabWidget(parent) {
    initialize();
    createOverviewTab();
    createEmployeeTab();
    setUpValidators();
    refreshEmployeeListView();
}

void CompanyTabWidget::initialize() {
    id = 5;
    ps = new PayrollSystem();
    QString companyName = ps->getNameOfCompany();
    this->setTabText(this->currentIndex(), companyName);
    this->currentChanged(this->currentIndex());
    ps->addEmployee("E1", "Calvin", "Pham", "Male", "Software Engineer", "1234 Fake Street", "Fake City", "California", "12345", 40.5, 40);
    ps->addEmployee("E2", "Paul", "French", "Male", "Software Engineer", "1234 Fake Street", "Fake City", "California", "12316", 12, 45);
}

void CompanyTabWidget::createOverviewTab() {
    overviewGroupBox = new QGroupBox("Company Info");
    QGridLayout *overviewLayout = new QGridLayout();

    overviewGroupBox->setLayout(overviewLayout);
    this->addTab(overviewGroupBox, "Overview");
}

void CompanyTabWidget::createEmployeeTab() {
    employeeGroupBox = new QGroupBox(tr("Add Employee"));

    QGridLayout *employeeLayout = new QGridLayout();

    QLabel *firstNameLabel = new QLabel();
    firstNameLabel->setText("First Name");
    firstNameLineEdit = new QLineEdit();

    employeeLayout->addWidget(firstNameLabel, 0, 0);
    employeeLayout->addWidget(firstNameLineEdit, 0, 1);

    QLabel *lastNameLabel = new QLabel();
    lastNameLabel->setText("Last Name");
    lastNameLineEdit = new QLineEdit();

    employeeLayout->addWidget(lastNameLabel, 1, 0);
    employeeLayout->addWidget(lastNameLineEdit, 1, 1);

    QLabel *genderLabel = new QLabel();
    genderLabel->setText("Gender");
    genderComboBox = new QComboBox();
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");

    employeeLayout->addWidget(genderLabel, 2, 0);
    employeeLayout->addWidget(genderComboBox, 2, 1);

    QLabel *jobPositionLabel = new QLabel();
    jobPositionLabel->setText("Job Position");
    jobPositionLineEdit = new QLineEdit();

    employeeLayout->addWidget(jobPositionLabel, 3, 0);
    employeeLayout->addWidget(jobPositionLineEdit, 3, 1);

    QLabel *streetAddressLabel = new QLabel();
    streetAddressLabel->setText("Street Address");
    streetAddressLineEdit = new QLineEdit();

    employeeLayout->addWidget(streetAddressLabel, 4, 0);
    employeeLayout->addWidget(streetAddressLineEdit, 4, 1);

    QLabel *cityLabel = new QLabel();
    cityLabel->setText("City");
    cityLineEdit = new QLineEdit();

    employeeLayout->addWidget(cityLabel, 5, 0);
    employeeLayout->addWidget(cityLineEdit, 5, 1);

    QLabel *stateLabel = new QLabel();
    stateLabel->setText("State");
    stateLineEdit = new QLineEdit();

    employeeLayout->addWidget(stateLabel, 6, 0);
    employeeLayout->addWidget(stateLineEdit, 6, 1);

    QLabel *zipcodeLabel = new QLabel();
    zipcodeLabel->setText("Zipcode");
    zipcodeLineEdit = new QLineEdit();

    employeeLayout->addWidget(zipcodeLabel, 7, 0);
    employeeLayout->addWidget(zipcodeLineEdit, 7, 1);

    QLabel *hourlyWageLabel = new QLabel();
    hourlyWageLabel->setText("Hourly Wage");
    hourlyWageLineEdit = new QLineEdit();

    employeeLayout->addWidget(hourlyWageLabel, 8, 0);
    employeeLayout->addWidget(hourlyWageLineEdit, 8, 1);

    QLabel *numberOfHoursLabel = new QLabel();
    numberOfHoursLabel->setText("Number of hours worked");
    numberOfHoursLineEdit = new QLineEdit();

    employeeLayout->addWidget(numberOfHoursLabel, 9, 0);
    employeeLayout->addWidget(numberOfHoursLineEdit, 9, 1);

    employeeListView = new QListView();
    employeeListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(employeeListView, SIGNAL(clicked(QModelIndex)), this, SLOT(employeeListViewClicked(QModelIndex)));
    // 0 is the starting row, 4 is the starting column, 10 is the length (top to bottom), 4 is width (left to right)
    employeeLayout->addWidget(employeeListView, 0, 4, 10, 4);

    addButton = new QPushButton("Add");
    connect(addButton, SIGNAL (clicked()), SLOT (addEmployee()));

    editButton = new QPushButton("Edit");
    connect(editButton, SIGNAL (clicked()), SLOT (editEmployee()));

    removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));

    employeeLayout->addWidget(addButton, 10, 0);
    employeeLayout->addWidget(editButton, 10, 1);
    employeeLayout->addWidget(removeButton, 10, 2);

    employeeGroupBox->setLayout(employeeLayout);

    connect(this, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));
    this->addTab(employeeGroupBox, "Employees");
}

void CompanyTabWidget::addEmployee() {
    QString employeeId = "E" + QString::number(id);
    QString firstName = firstNameLineEdit->text();
    QString lastName = lastNameLineEdit->text();
    QString gender = genderComboBox->currentText();
    QString jobPosition = jobPositionLineEdit->text();
    QString streetAddress = streetAddressLineEdit->text();
    QString city = cityLineEdit->text();
    QString state = stateLineEdit->text();
    QString zipcode = zipcodeLineEdit->text();
    double hourlyWage = hourlyWageLineEdit->text().toDouble();
    int numberOfHours = numberOfHoursLineEdit->text().toInt();

    ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
    id++;

    refreshEmployeeListView();
}

void CompanyTabWidget::setUpValidators() {
    // You can try QDoubleValidator and QIntValidator
    QRegExpValidator* integerValidator = new QRegExpValidator(QRegExp("\\d*"));
    QRegExpValidator* doubleValidator = new QRegExpValidator(QRegExp("\\d*\\.?\\d"));
    QRegExpValidator* zipcodeValidator = new QRegExpValidator(QRegExp("^[0-9]{5}(?:-[0-9]{4})?$"));
    hourlyWageLineEdit->setValidator(doubleValidator);
    numberOfHoursLineEdit->setValidator(integerValidator);
    zipcodeLineEdit->setValidator(zipcodeValidator);
}

void CompanyTabWidget::refreshEmployeeListView() {
    QStringListModel *model = new QStringListModel();
    QStringList list = ps->getStringListOfEmployees();
    model->setStringList(list);
    employeeListView->setModel(model);
}

void CompanyTabWidget::employeeListViewClicked(const QModelIndex &index)
{
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QStringList employeeInfo = employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    Employee employee = ps->getEmployeeById(employeeInfo[0]);
    firstNameLineEdit->setText(employee.getFirstName());
    lastNameLineEdit->setText(employee.getLastName());
    genderComboBox->setCurrentText(employee.getGender());
    jobPositionLineEdit->setText(employee.getJobPosition());
    streetAddressLineEdit->setText(employee.getStreetAddress());
    cityLineEdit->setText(employee.getCity());
    stateLineEdit->setText(employee.getState());
    zipcodeLineEdit->setText(employee.getZipcode());
    hourlyWageLineEdit->setText(QString::number(employee.getHourlyWage()));
    numberOfHoursLineEdit->setText(QString::number(employee.getNumberOfHours()));
}

void CompanyTabWidget::tabChanged(int index)
{
    if (index == 1) {
        refreshEmployeeListView();
    }
}


void CompanyTabWidget::clearForms() {
    // Clear forms
    foreach(QLineEdit* le, this->findChildren<QLineEdit*>()) {
        le->clear();
    }
}

void CompanyTabWidget::removeEmployee()
{
    if (employeeListView->currentIndex().isValid() == false) {
        return;
    }
    const QModelIndex &index = employeeListView->currentIndex();
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QStringList employeeInfo = employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    ps->removeEmployeeById(employeeInfo[0]);

    refreshEmployeeListView();
    clearForms();
}

void CompanyTabWidget::editEmployee()
{
    const QModelIndex &index = employeeListView->currentIndex();
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QStringList employeeInfo = employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    QString employeeId = employeeInfo[0];
    QString firstName = firstNameLineEdit->text();
    QString lastName = lastNameLineEdit->text();
    QString gender = genderComboBox->currentText();
    QString jobPosition = jobPositionLineEdit->text();
    QString streetAddress = streetAddressLineEdit->text();
    QString city = cityLineEdit->text();
    QString state = stateLineEdit->text();
    QString zipcode = zipcodeLineEdit->text();
    double hourlyWage = hourlyWageLineEdit->text().toDouble();
    int numberOfHours = numberOfHoursLineEdit->text().toInt();

    ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
    refreshEmployeeListView();
}
