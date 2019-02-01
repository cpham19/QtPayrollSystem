#include "headers/companytabwidget.h"
#include "headers/globals.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent, QString name): QTabWidget(parent) {
    initializeData(name);
    createOverviewTab();
    createEmployeeTableTab();

    //timerId = startTimer(1000);
}

CompanyTabWidget::~CompanyTabWidget()
{
    //killTimer(timerId);
    delete this;
}

void CompanyTabWidget::initializeData(QString name) {
    id = 50;
    ps = new PayrollSystem();
    ps->setNameOfCompany(name);

    // This will generate different seed for every new tab (apparently rand() is not good in modern times but I needed something to give me a new seed everytime I open a tab)
    mt19937 generator(rand());
    uniform_real_distribution<double> doubleDistribution(1.0,50.0);
    uniform_int_distribution<int> numberOfEmployeesDistribution(1,40);

    // Each distribution has a different size for each text file
    uniform_int_distribution<int> maleFirstNamesDistribution(0, maleFirstNames.size() - 1);
    uniform_int_distribution<int> femaleFirstNamesDistribution(0, femaleFirstNames.size() - 1);
    uniform_int_distribution<int> genderDistribution(0, 1);
    uniform_int_distribution<int> lastNamesDistribution(0, lastNames.size() - 1);
    uniform_int_distribution<int> jobsDistribution(0, jobs.size() - 1);
    uniform_int_distribution<int> streetsDistribution(0, streets.size() - 1);
    uniform_int_distribution<int> streetSuffixesDistribution(0, streetSuffixes.size() - 1);
    uniform_int_distribution<int> citiesDistribution(0, cities.size() - 1);
    uniform_int_distribution<int> statesDistribution(0, states.size() - 1);
    uniform_int_distribution<int> zipcodesDistribution(0, zipcodes.size() - 1);

    // numbers between 1 and 40 (inclusive)
    int numberOfEmployees = numberOfEmployeesDistribution(generator);

    for (int i = 1; i <= numberOfEmployees; i++) {
        QString id = "E" + QString::number(i);
        QString gender;
        QString firstName;

        if ((int) genderDistribution(generator) == 0 ) {
            gender = "Male";
            firstName = maleFirstNames[maleFirstNamesDistribution(generator)];
        }
        else {
            gender = "Female";
            firstName = femaleFirstNames[femaleFirstNamesDistribution(generator)];
        }

        QString lastName = lastNames[lastNamesDistribution(generator)];
        QString position = jobs[jobsDistribution(generator)];
        QString street = streets[streetsDistribution(generator)] + " " + streetSuffixes[streetSuffixesDistribution(generator)];
        QString city = cities[citiesDistribution(generator)];
        QString state = states[statesDistribution(generator)];
        QString zipcode = zipcodes[zipcodesDistribution(generator)];
        double hourlyWage = QString::number(doubleDistribution(generator), 'f', 2).toDouble();
        int numberOfHours =  numberOfEmployeesDistribution(generator);

        ps->addEmployee(id, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours);
    }

    this->setStyleSheet("QTabBar::tab { height: 25px; width: 100px;}");
}

void CompanyTabWidget::createOverviewTab() {
    overviewGroupBox = new QGroupBox("Company Info");
    overviewLayout = new QGridLayout();

    nameOfCompanyLabel = new QLabel();
    nameOfCompanyLabel->setText("Company Name: " + ps->getNameOfCompany());
    overviewLayout->addWidget(nameOfCompanyLabel, 0, 0);

    numberOfEmployeesLabel = new QLabel();
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    overviewLayout->addWidget(numberOfEmployeesLabel, 1, 0);

    totalAmountPaidLabel = new QLabel();
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount()));
    overviewLayout->addWidget(totalAmountPaidLabel, 2, 0);

    overviewGroupBox->setLayout(overviewLayout);
    this->addTab(overviewGroupBox, "Overview");
}

void CompanyTabWidget::createEmployeeTableTab() {
    tableGroupBox = new QGroupBox("List of Employees");
    QGridLayout *tableLayout = new QGridLayout();

    setUpEmployeeTable();

    addButton = new QPushButton("Add");
    removeButton = new QPushButton("Remove");
    payAllButton = new QPushButton("Pay All");

    connect(addButton, SIGNAL (clicked()), SLOT (toggleAddDialog()));
    connect(employeeTableView,SIGNAL(doubleClicked(const QModelIndex&)), SLOT (toggleEditDialog()));
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));
    connect(payAllButton, SIGNAL (clicked()), SLOT (payAllEmployees()));

    tableLayout->addWidget(employeeTableView, 0, 0, 10, 3);
    tableLayout->addWidget(addButton, 11, 0);
    tableLayout->addWidget(removeButton, 11, 1);
    tableLayout->addWidget(payAllButton, 11, 2);

    tableGroupBox->setLayout(tableLayout);
    this->addTab(tableGroupBox, "Employees");
}

void CompanyTabWidget::setUpValidators() {
    // You can try QDoubleValidator and QIntValidator
    QRegExpValidator* integerValidator = new QRegExpValidator(QRegExp("\\d*"));
    QRegExpValidator* doubleValidator = new QRegExpValidator(QRegExp("\\d*\\.?\\d\\d"));
    QRegExpValidator* zipcodeValidator = new QRegExpValidator(QRegExp("^[0-9]{5}(?:-[0-9]{4})?$"));
    QRegExpValidator* stringValidator = new QRegExpValidator(QRegExp("[a-zA-Z]+"));
    QRegExpValidator* stringWithSpacesValidator = new QRegExpValidator(QRegExp("^[a-zA-Z0-9_]+( [a-zA-Z0-9_]+)*$"));

    firstNameLineEdit->setValidator(stringValidator);
    lastNameLineEdit->setValidator(stringValidator);
    jobPositionLineEdit->setValidator(stringWithSpacesValidator);
    streetAddressLineEdit->setValidator(stringWithSpacesValidator);
    zipcodeLineEdit->setValidator(zipcodeValidator);
    hourlyWageLineEdit->setValidator(doubleValidator);
    numberOfHoursLineEdit->setValidator(integerValidator);
}

void CompanyTabWidget::setUpEmployeeTable() {
    employeeTableView = new QTableView();
    employeeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    employeeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    employeeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeeTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    vector<Employee> list = ps->getPayrollList();
    tableViewModel = new EmployeeTableModel(list);
    employeeTableView->setModel(tableViewModel);
}


void CompanyTabWidget::tabChanged(int index)
{

}

void CompanyTabWidget::removeEmployee()
{
    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }
    const QModelIndex &index = employeeTableView->currentIndex();
    const int row = employeeTableView->currentIndex().row();

    QString employeeId = tableViewModel->data(tableViewModel->index(row, 0), Qt::DisplayRole).toString();

    qDebug() << employeeId;

    ps->removeEmployeeById(employeeId);

    update();
}

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qtcreator
void CompanyTabWidget::toggleAddDialog() {
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Add an Employee"));

    firstNameLabel = new QLabel();
    firstNameLabel->setText("First Name");
    firstNameLineEdit = new QLineEdit(&dialog);

    lastNameLabel = new QLabel();
    lastNameLabel->setText("Last Name");
    lastNameLineEdit = new QLineEdit(&dialog);

    genderComboBoxLabel = new QLabel();
    genderComboBoxLabel->setText("Gender");
    genderComboBox = new QComboBox(&dialog);
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");

    jobPositionLabel = new QLabel();
    jobPositionLabel->setText("Job Position");
    jobPositionLineEdit = new QLineEdit(&dialog);

    streetAddressLabel = new QLabel();
    streetAddressLabel->setText("Street Address");
    streetAddressLineEdit = new QLineEdit(&dialog);

    cityLabel = new QLabel();
    cityLabel->setText("City");
    cityComboBox = new QComboBox(&dialog);
    for (QString city : cities) {
        cityComboBox->addItem(city);
    }

    stateLabel = new QLabel();
    stateLabel->setText("State");
    stateComboBox = new QComboBox(&dialog);
    for (QString state : states) {
        stateComboBox->addItem(state);
    }

    zipcodeLabel = new QLabel();
    zipcodeLabel->setText("Zipcode");
    zipcodeLineEdit = new QLineEdit(&dialog);

    hourlyWageLabel = new QLabel();
    hourlyWageLabel->setText("Hourly Wage");
    hourlyWageLineEdit = new QLineEdit(&dialog);

    numberOfHoursLabel = new QLabel();
    numberOfHoursLabel->setText("Number of hours worked");
    numberOfHoursLineEdit = new QLineEdit(&dialog);

    setUpValidators();

    form.addRow(firstNameLabel, firstNameLineEdit);
    form.addRow(lastNameLabel, lastNameLineEdit);
    form.addRow(genderComboBoxLabel, genderComboBox);
    form.addRow(jobPositionLabel, jobPositionLineEdit);
    form.addRow(streetAddressLabel, streetAddressLineEdit);
    form.addRow(cityLabel, cityComboBox);
    form.addRow(stateLabel, stateComboBox);
    form.addRow(zipcodeLabel, zipcodeLineEdit);
    form.addRow(hourlyWageLabel, hourlyWageLineEdit);
    form.addRow(numberOfHoursLabel, numberOfHoursLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString employeeId = "E" + QString::number(id);
        QString firstName = firstNameLineEdit->text();
        QString lastName = lastNameLineEdit->text();
        QString gender = genderComboBox->currentText();
        QString jobPosition = jobPositionLineEdit->text();
        QString streetAddress = streetAddressLineEdit->text();
        QString city = cityComboBox->currentText();
        QString state = stateComboBox->currentText();
        QString zipcode = zipcodeLineEdit->text();
        double hourlyWage = hourlyWageLineEdit->text().toDouble();
        int numberOfHours = numberOfHoursLineEdit->text().toInt();

        ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
        id++;
    }

    update();
}

void CompanyTabWidget::toggleEditDialog() {
    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }
    const QModelIndex &index = employeeTableView->currentIndex();
    const int row = employeeTableView->currentIndex().row();

    QString employeeId = tableViewModel->data(tableViewModel->index(row, 0), Qt::DisplayRole).toString();
    QString oldFirstName = tableViewModel->data(tableViewModel->index(row, 1), Qt::DisplayRole).toString();
    QString oldLastName = tableViewModel->data(tableViewModel->index(row, 2), Qt::DisplayRole).toString();
    QString oldGender = tableViewModel->data(tableViewModel->index(row, 3), Qt::DisplayRole).toString();
    QString oldPosition = tableViewModel->data(tableViewModel->index(row, 4), Qt::DisplayRole).toString();
    QString oldStreet = tableViewModel->data(tableViewModel->index(row, 5), Qt::DisplayRole).toString();
    QString oldCity = tableViewModel->data(tableViewModel->index(row, 6), Qt::DisplayRole).toString();
    QString oldState = tableViewModel->data(tableViewModel->index(row, 7), Qt::DisplayRole).toString();
    QString oldZipcode = tableViewModel->data(tableViewModel->index(row, 8), Qt::DisplayRole).toString();
    double oldHourlyWage = tableViewModel->data(tableViewModel->index(row, 9), Qt::DisplayRole).toDouble();
    int oldNumberOfHours = tableViewModel->data(tableViewModel->index(row, 10), Qt::DisplayRole).toInt();

    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Add an Employee"));

    firstNameLabel = new QLabel();
    firstNameLabel->setText("First Name");
    firstNameLineEdit = new QLineEdit(&dialog);
    firstNameLineEdit->setText(oldFirstName);

    lastNameLabel = new QLabel();
    lastNameLabel->setText("Last Name");
    lastNameLineEdit = new QLineEdit(&dialog);
    lastNameLineEdit->setText(oldLastName);

    genderComboBoxLabel = new QLabel();
    genderComboBoxLabel->setText("Gender");
    genderComboBox = new QComboBox(&dialog);
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");
    genderComboBox->setCurrentText(oldGender);

    jobPositionLabel = new QLabel();
    jobPositionLabel->setText("Job Position");
    jobPositionLineEdit = new QLineEdit(&dialog);
    jobPositionLineEdit->setText(oldPosition);

    streetAddressLabel = new QLabel();
    streetAddressLabel->setText("Street Address");
    streetAddressLineEdit = new QLineEdit(&dialog);
    streetAddressLineEdit->setText(oldStreet);

    cityLabel = new QLabel();
    cityLabel->setText("City");
    cityComboBox = new QComboBox(&dialog);
    for (QString city : cities) {
        cityComboBox->addItem(city);
    }
    cityComboBox->setCurrentText(oldCity);

    stateLabel = new QLabel();
    stateLabel->setText("State");
    stateComboBox = new QComboBox(&dialog);
    for (QString state : states) {
        stateComboBox->addItem(state);
    }
    stateComboBox->setCurrentText(oldState);

    zipcodeLabel = new QLabel();
    zipcodeLabel->setText("Zipcode");
    zipcodeLineEdit = new QLineEdit(&dialog);
    zipcodeLineEdit->setText(oldZipcode);

    hourlyWageLabel = new QLabel();
    hourlyWageLabel->setText("Hourly Wage");
    hourlyWageLineEdit = new QLineEdit(&dialog);
    hourlyWageLineEdit->setText(QString::number(oldHourlyWage));

    numberOfHoursLabel = new QLabel();
    numberOfHoursLabel->setText("Number of hours worked");
    numberOfHoursLineEdit = new QLineEdit(&dialog);
    numberOfHoursLineEdit->setText(QString::number(oldNumberOfHours));

    setUpValidators();

    form.addRow(firstNameLabel, firstNameLineEdit);
    form.addRow(lastNameLabel, lastNameLineEdit);
    form.addRow(genderComboBoxLabel, genderComboBox);
    form.addRow(jobPositionLabel, jobPositionLineEdit);
    form.addRow(streetAddressLabel, streetAddressLineEdit);
    form.addRow(cityLabel, cityComboBox);
    form.addRow(stateLabel, stateComboBox);
    form.addRow(zipcodeLabel, zipcodeLineEdit);
    form.addRow(hourlyWageLabel, hourlyWageLineEdit);
    form.addRow(numberOfHoursLabel, numberOfHoursLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString firstName = firstNameLineEdit->text();
        QString lastName = lastNameLineEdit->text();
        QString gender = genderComboBox->currentText();
        QString jobPosition = jobPositionLineEdit->text();
        QString streetAddress = streetAddressLineEdit->text();
        QString city = cityComboBox->currentText();
        QString state = stateComboBox->currentText();
        QString zipcode = zipcodeLineEdit->text();
        double hourlyWage = hourlyWageLineEdit->text().toDouble();
        int numberOfHours = numberOfHoursLineEdit->text().toInt();

        ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
    }

    update();
}

void CompanyTabWidget::update() {
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount()));

    vector<Employee> list = ps->getPayrollList();
    tableViewModel = new EmployeeTableModel(list);
    employeeTableView->setModel(tableViewModel);
}

void CompanyTabWidget::payAllEmployees() {
    ps->issuePaychecks();
    update();
}

void CompanyTabWidget::timerEvent(QTimerEvent *event)
{
//        ps->incrementHoursOfEmployees();
//        update();
}
