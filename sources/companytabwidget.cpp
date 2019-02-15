#include "headers/companytabwidget.h"
#include "headers/globals.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent, QString name): QTabWidget(parent) {
    initializeData(name);
    createOverviewTab();
    createEmployeeTableTab();
    createOutputTab();

    createTimer();
}

CompanyTabWidget::~CompanyTabWidget()
{
    stopTimer();
    delete this;
}

void CompanyTabWidget::createTimer() {
    timerId = startTimer(2000);
}

void CompanyTabWidget::stopTimer() {
    killTimer(timerId);
}

void CompanyTabWidget::initializeData(QString name) {
    id = 1;
    ps = new PayrollSystem();
    ps->setNameOfCompany(name);

    this->setStyleSheet("QTabBar::tab { height: 25px; width: 400px;}");
}

void CompanyTabWidget::generateRandomEmployees() {
    // This will generate different seed for every new tab (apparently rand() is not good in modern times but I needed something to give me a new seed everytime I open a tab)
    mt19937 generator(rand());
    uniform_real_distribution<double> doubleDistribution(10.0,50.0);
    uniform_int_distribution<int> numberOfEmployeesDistribution(15,40);

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
        QString employeeId = "E" + QString::number(id);
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

        ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours);
        tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours);

        id++;
    }

    update();
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
    tableLayout = new QGridLayout();

    setUpEmployeeTable();

    addButton = new QPushButton("Add");
    generateEmployeesButton = new QPushButton("Generate Employees");
    removeButton = new QPushButton("Remove");
    payAllButton = new QPushButton("Pay All");

    connect(addButton, SIGNAL (clicked()), SLOT (toggleAddDialog()));
    connect(employeeTableView,SIGNAL(doubleClicked(const QModelIndex&)), SLOT (toggleEditDialog()));
    connect(generateEmployeesButton, SIGNAL (clicked()), SLOT(generateRandomEmployees()));
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));
    connect(payAllButton, SIGNAL (clicked()), SLOT (payAllEmployees()));

    tableLayout->addWidget(employeeTableView, 0, 0, 10, 4);
    tableLayout->addWidget(addButton, 11, 0);
    tableLayout->addWidget(generateEmployeesButton, 11, 1);
    tableLayout->addWidget(removeButton, 11, 2);
    tableLayout->addWidget(payAllButton, 11, 3);

    tableGroupBox->setLayout(tableLayout);
    this->addTab(tableGroupBox, "Employees");
}

void CompanyTabWidget::createOutputTab() {
    outputGroupBox = new QGroupBox("Save Options");
    outputLayout = new QGridLayout();

    saveToFileButton = new QPushButton("Save Company Details To File");
    connect(saveToFileButton, SIGNAL (clicked()), SLOT(saveToFile()));
    outputLayout->addWidget(saveToFileButton);

    outputGroupBox->setLayout(outputLayout);
    this->addTab(outputGroupBox, "Output");
}

void CompanyTabWidget::saveToFile() {
    stopTimer();

    QString fileName = ps->getNameOfCompany() + ".csv";
    QString path = qApp->applicationDirPath() + "/csv/" + fileName;
    QFile file(path);
    file.remove();

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "name of company,number of employees,amount paid ($)" << endl;
        stream << ps->getNameOfCompany() + "," + QString::number(ps->getPayrollList().size()) + "," + QString::number(ps->getTotalAmount()) << endl;
        stream << endl << endl;

        stream << "employee id,first name,last name,gender,job position,street address,city,state,zipcode,hourly wage,hours worked,amount to be paid ($)" << endl;

        for (int i = 0; i < ps->getPayrollList().size(); i++) {
            Employee e = ps->getPayrollList()[i];
            stream << e.getEmployeeId() + "," + e.getFirstName() + "," + e.getLastName() + "," + e.getGender() + "," + e.getJobPosition() + "," + e.getStreetAddress() + "," + e.getCity() + "," + e.getState() + "," + e.getZipcode() + "," + QString::number(e.getHourlyWage()) + "," + QString::number(e.getNumberOfHours()) + "," + QString::number(e.getHourlyWage() * e.getNumberOfHours()) << endl;
        }
    }

    file.close();

    createTimer();
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
    tableViewModel = new EmployeeTableModel(ps);
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

    ps->removeEmployeeById(employeeId);

    tableViewModel->removeRowByRow(employeeId, row);

    mainLog->append(getCurrentTimeStamp() + " Removed Employee #" + employeeId);

    update();
}

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qtcreator
void CompanyTabWidget::toggleAddDialog() {
    stopTimer();

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
    jobPositionComboBox = new QComboBox(&dialog);
    for (QString position : jobs) {
        jobPositionComboBox->addItem(position);
    }

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
    form.addRow(jobPositionLabel, jobPositionComboBox);
    form.addRow(streetAddressLabel, streetAddressLineEdit);
    form.addRow(cityLabel, cityComboBox);
    form.addRow(stateLabel, stateComboBox);
    form.addRow(zipcodeLabel, zipcodeLineEdit);
    form.addRow(hourlyWageLabel, hourlyWageLineEdit);
    form.addRow(numberOfHoursLabel, numberOfHoursLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    QPushButton *autofillButton = new QPushButton("Autofill forms");
    connect(autofillButton, SIGNAL (clicked()), SLOT (automaticallyFill()));
    buttonBox.addButton(autofillButton, QDialogButtonBox::ActionRole);

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
        QString jobPosition = jobPositionComboBox->currentText();
        QString streetAddress = streetAddressLineEdit->text();
        QString city = cityComboBox->currentText();
        QString state = stateComboBox->currentText();
        QString zipcode = zipcodeLineEdit->text();
        double hourlyWage = hourlyWageLineEdit->text().toDouble();
        int numberOfHours = numberOfHoursLineEdit->text().toInt();

        ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);
        tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        mainLog->append(getCurrentTimeStamp() + " Added Employee# " + employeeId);

        id++;
    }

    createTimer();
}

void CompanyTabWidget::toggleEditDialog() {
    stopTimer();

    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }
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
    jobPositionComboBox = new QComboBox(&dialog);
    for (QString position : jobs) {
        jobPositionComboBox->addItem(position);
    }
    jobPositionComboBox->setCurrentText(oldPosition);

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
    form.addRow(jobPositionLabel, jobPositionComboBox);
    form.addRow(streetAddressLabel, streetAddressLineEdit);
    form.addRow(cityLabel, cityComboBox);
    form.addRow(stateLabel, stateComboBox);
    form.addRow(zipcodeLabel, zipcodeLineEdit);
    form.addRow(hourlyWageLabel, hourlyWageLineEdit);
    form.addRow(numberOfHoursLabel, numberOfHoursLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    QPushButton *autofillButton = new QPushButton("Autofill forms");
    connect(autofillButton, SIGNAL (clicked()), SLOT (automaticallyFill()));
    buttonBox.addButton(autofillButton, QDialogButtonBox::ActionRole);

    form.addRow(&buttonBox);
    connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString firstName = firstNameLineEdit->text();
        QString lastName = lastNameLineEdit->text();
        QString gender = genderComboBox->currentText();
        QString jobPosition = jobPositionComboBox->currentText();
        QString streetAddress = streetAddressLineEdit->text();
        QString city = cityComboBox->currentText();
        QString state = stateComboBox->currentText();
        QString zipcode = zipcodeLineEdit->text();
        double hourlyWage = hourlyWageLineEdit->text().toDouble();
        int numberOfHours = numberOfHoursLineEdit->text().toInt();

        ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        tableViewModel->editRow(row, employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        mainLog->append(getCurrentTimeStamp() + " Editted Employee# " + employeeId);

        update();
    }

    createTimer();
}

void CompanyTabWidget::automaticallyFill() {
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

    firstNameLineEdit->setText(firstName);
    lastNameLineEdit->setText(lastName);
    genderComboBox->setCurrentText(gender);
    jobPositionComboBox->setCurrentText(position);
    streetAddressLineEdit->setText(street);
    cityComboBox->setCurrentText(city);
    stateComboBox->setCurrentText(state);
    zipcodeLineEdit->setText(zipcode);
    hourlyWageLineEdit->setText(QString::number(hourlyWage));
    numberOfHoursLineEdit->setText(QString::number(numberOfHours));
}

void CompanyTabWidget::update() {
    nameOfCompanyLabel->setText("Company Name: " + ps->getNameOfCompany());
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount()));
}

void CompanyTabWidget::addEmployeeByQStringList(QStringList list) {
    QString employeeId = list[0];
    QString firstName = list[1];
    QString lastName = list[2];
    QString gender = list[3];
    QString position = list[4];
    QString street = list[5];
    QString city = list[6];
    QString state = list[7];
    QString zipcode = list[8];
    double hourlyWage = list[9].toDouble();
    int numberOfHours = list[10].toInt();

    ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours);
    tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours);

    id++;

    update();
}

void CompanyTabWidget::payAllEmployees() {
    stopTimer();

    ps->issuePaychecks();

    tableViewModel->payAllRows();

    update();

    mainLog->append("Paid all employees in " + ps->getNameOfCompany() + ".");

    createTimer();
}

void CompanyTabWidget::timerEvent(QTimerEvent *event)
{
    ps->incrementHoursOfEmployees();

    tableViewModel->incrementHours();
    // update();
}

QString CompanyTabWidget::getCurrentTimeStamp() const {
    QString timestamp = "[" + QDateTime::currentDateTime().toString() + "]";
    return timestamp;
}
