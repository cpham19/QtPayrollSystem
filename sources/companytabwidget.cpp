#include "headers/companytabwidget.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent, QString name): QTabWidget(parent) {
    // Initializing data and creating tabs
    initializeData(name);
    createOverviewTab();
    createEmployeeTableTab();
    createStatisticsTab();
    createOutputTab();
}

CompanyTabWidget::~CompanyTabWidget()
{
    stopTimer();
    delete this;
}

// Starting timer for increasing hours
void CompanyTabWidget::startTimer() {
    clock->startTimer();
}

// Stopping the timer
void CompanyTabWidget::stopTimer() {
    clock->stopTimer();
}

void CompanyTabWidget::initializeData(QString name) {
    id = 1;
    ps = new PayrollSystem();
    ps->setNameOfCompany(name);
    ps->setBudget(0.00);

    this->setStyleSheet("QTabBar::tab { height: 25px; width: 300px;}");
}

void CompanyTabWidget::generateRandomEmployees() {
    if (timerButton->text().compare("Stop Timer") == 0) {
        toggleTimerButton();
    }

    // This will generate different seed for every new tab (apparently rand() is not good in modern times but I needed something to give me a new seed everytime I open a tab)
    mt19937 generator(rand());
    uniform_real_distribution<double> doubleDistribution(10.0,50.0);
    uniform_int_distribution<int> numberOfEmployeesDistribution(15,40);
    uniform_int_distribution<int> numberOfHoursDistribution(0,10);

    // Each distribution has a different size for each text file
    uniform_int_distribution<int> maleFirstNamesDistribution(0, maleFirstNames.size() - 1);
    uniform_int_distribution<int> femaleFirstNamesDistribution(0, femaleFirstNames.size() - 1);
    uniform_int_distribution<int> genderDistribution(0, 1);
    uniform_int_distribution<int> lastNamesDistribution(0, lastNames.size() - 1);
    uniform_int_distribution<int> *jobsDistribution = new uniform_int_distribution<int>(0, jobs.size() - 1);
    uniform_int_distribution<int> streetsDistribution(0, streets.size() - 1);
    uniform_int_distribution<int> streetSuffixesDistribution(0, streetSuffixes.size() - 1);
    uniform_int_distribution<int> citiesDistribution(0, cities.size() - 1);
    uniform_int_distribution<int> statesDistribution(0, states.size() - 1);
    uniform_int_distribution<int> zipcodesDistribution(0, zipcodes.size() - 1);

    // numbers between 1 and 40 (inclusive)
    int numberOfEmployees = numberOfEmployeesDistribution(generator);

    // create employees based on RNG settings
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
        int indexOfPosition = jobsDistribution->operator()(generator);
        QString position = jobs[indexOfPosition];

        if (position.compare("Chief Executive Officer") == 0 || position.compare("Chief Operating Officer") == 0 || position.compare("President") == 0 || position.compare("Chief Financial Officer") == 0 || position.compare("Chief Marketing Officer") == 0 || position.compare("Chief Technology Officer") == 0) {
            jobs.erase(jobs.begin() + indexOfPosition);
            jobsDistribution = new uniform_int_distribution<int>(0, jobs.size() - 1);
        }

        QString street = streets[streetsDistribution(generator)] + " " + streetSuffixes[streetSuffixesDistribution(generator)];
        QString city = cities[citiesDistribution(generator)];
        QString state = states[statesDistribution(generator)];
        QString zipcode = zipcodes[zipcodesDistribution(generator)];
        //int numberOfHours =  numberOfEmployeesDistribution(generator);
        int numberOfHours = 0;
        int totalNumberOfHours = 0;
        int numberOfOvertimeHours =  0;
        int totalNumberOfOvertimeHours = 0;
        double hourlyWage = QString::number(doubleDistribution(generator), 'f', 2).toDouble();
        double amountToBePaid = 0.00;
        double totalAmountPaid = 0.00;

        ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);
        employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);

        id++;
    }

    // Object structure {"Chief Executive Officer": 1, "Chief Marketing Officer": 1, "Chief Technology Officer": 0, "Chief Operating Officer": 0, "President": 0}, 1 meaning the position is occupied and 0 meaning not occupied
    QJsonObject officerObj = ps->checkForOfficers();

    // create a CEO if it doesn't exist yet
    foreach(const QString& key, officerObj.keys()) {
        if (officerObj[key] == 0) {
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

            QString position = key;
            QString street = streets[streetsDistribution(generator)] + " " + streetSuffixes[streetSuffixesDistribution(generator)];
            QString city = cities[citiesDistribution(generator)];
            QString state = states[statesDistribution(generator)];
            QString zipcode = zipcodes[zipcodesDistribution(generator)];
            //int numberOfHours =  numberOfEmployeesDistribution(generator);
            int numberOfHours = 0;
            int totalNumberOfHours = 0;
            int numberOfOvertimeHours =  0;
            int totalNumberOfOvertimeHours = 0;
            double hourlyWage = QString::number(doubleDistribution(generator), 'f', 2).toDouble();
            double amountToBePaid = 0.00;
            double totalAmountPaid = 0.00;

            ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);
            employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);

            id++;
        }
    }

    update();
}

// Used for creating overview tab
void CompanyTabWidget::createOverviewTab() {
    overviewGroupBox = new QGroupBox("Company Info");
    overviewLayout = new QGridLayout();

    nameOfCompanyLabel = new QLabel();
    nameOfCompanyLabel->setText("Company Name: " + ps->getNameOfCompany());
    overviewLayout->addWidget(nameOfCompanyLabel, 0, 0);

    nameOfCEOLabel = new QLabel();

    if (ps->getPayrollList().size() == 0) {
        nameOfCEOLabel->setText("Chief Executive Officer: None");
    }
    else {
        nameOfCEOLabel->setText("Chief Executive Officer: " + ps->getCEO());
    }

    overviewLayout->addWidget(nameOfCEOLabel, 1, 0);

    numberOfEmployeesLabel = new QLabel();
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    overviewLayout->addWidget(numberOfEmployeesLabel, 2, 0);

    totalAmountPaidLabel = new QLabel();
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount()));
    overviewLayout->addWidget(totalAmountPaidLabel, 3, 0);

    overviewGroupBox->setLayout(overviewLayout);
    this->addTab(overviewGroupBox, QIcon(qApp->applicationDirPath() + "/img/overview.ico"), "Overview");
}

//. Used for creating employee table tab
void CompanyTabWidget::createEmployeeTableTab() {
    tableGroupBox = new QGroupBox("List of Employees");
    tableLayout = new QGridLayout();

    employeeTableView = new EmployeeTableView(ps);

    addButton = new QPushButton("Add");
    generateEmployeesButton = new QPushButton("Generate Employees");
    removeButton = new QPushButton("Remove");
    payButton = new QPushButton("Pay");
    payAllButton = new QPushButton("Pay All");
    timerButton = new QPushButton("Start Timer");

    connect(addButton, SIGNAL (clicked()), SLOT (toggleAddDialog()));
    connect(employeeTableView,SIGNAL(doubleClicked(const QModelIndex&)), SLOT (toggleEditDialog()));
    connect(generateEmployeesButton, SIGNAL (clicked()), SLOT(generateRandomEmployees()));
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));
    connect(payButton, SIGNAL (clicked()), SLOT (payEmployee()));
    connect(payAllButton, SIGNAL (clicked()), SLOT (payAllEmployees()));
    connect(timerButton, SIGNAL (clicked()), SLOT (toggleTimerButton()));

    tableLayout->addWidget(employeeTableView, 1, 0, 11, 6);
    tableLayout->addWidget(addButton, 12, 0);
    tableLayout->addWidget(generateEmployeesButton, 12, 1);
    tableLayout->addWidget(removeButton, 12, 2);
    tableLayout->addWidget(payButton, 12, 3);
    tableLayout->addWidget(payAllButton, 12, 4);
    tableLayout->addWidget(timerButton, 12, 5);

    companyBudgetLabel = new QLabel();
    companyBudgetLabel->setText("Budget: $" + QString::number(ps->getBudget(), 'f', 2));
    tableLayout->addWidget(companyBudgetLabel, 0, 0);

    companyBudgetEditButton = new QPushButton("Edit Budget");
    connect(companyBudgetEditButton, SIGNAL (clicked()), SLOT(editBudget()));
    tableLayout->addWidget(companyBudgetEditButton, 0, 1);

    dateLabel = new QLabel();
    tableLayout->addWidget(dateLabel, 0, 2);

    meridiemLabel = new QLabel();
    tableLayout->addWidget(meridiemLabel, 0, 4);

    clock = new DigitalClock(timerButton, dateLabel, meridiemLabel, ps, employeeTableView);
    clock->show();
    tableLayout->addWidget(clock, 0, 3);

    tableGroupBox->setLayout(tableLayout);
    this->addTab(tableGroupBox, QIcon(qApp->applicationDirPath() + "/img/employee.ico"), "Employees");
}

// Used for creating statistics tab
void CompanyTabWidget::createStatisticsTab() {
    statsGroupBox = new QGroupBox("Stats");
    statsLayout = new StatisticsLayout(ps);

    statsGroupBox->setLayout(statsLayout);

    this->addTab(statsGroupBox, QIcon(qApp->applicationDirPath() + "/img/statistics.ico"), "Statistics");
}

// Used for creating the save details tab
void CompanyTabWidget::createOutputTab() {
    outputGroupBox = new QGroupBox("Save Options");
    outputLayout = new QGridLayout();

    saveToFileButton = new QPushButton("Save Company Details To File");
    connect(saveToFileButton, SIGNAL (clicked()), SLOT(saveToFile()));
    outputLayout->addWidget(saveToFileButton);

    outputGroupBox->setLayout(outputLayout);
    this->addTab(outputGroupBox, QIcon(qApp->applicationDirPath() + "/img/save.ico"), "Output");
}

// Used for saving details to csv files
void CompanyTabWidget::saveToFile() {
    if (timerButton->text().compare("Stop Timer") == 0) {
        toggleTimerButton();
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), qApp->applicationDirPath() + "/csv/" + ps->getNameOfCompany() + ".csv", tr("Comma-separated Values File (*.csv)"));
    QFile file(fileName);
    file.remove();

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);

        QString columns1 = "name of company,number of employees,budget per month,amount paid ($)";
        stream << columns1 << endl;
        stream << ps->getNameOfCompany() + "," + QString::number(ps->getPayrollList().size()) + "," + QString::number(ps->getBudget(), 'f', 2) + "," + QString::number(ps->getTotalAmount(), 'f', 2) << endl;
        stream << endl << endl;

        stream << "employee id,first name,last name,gender,job position,street address,city,state,zipcode,hours worked,total hours worked,overtimehours worked,total overtimehours worked,hourly wage,amount to be paid ($),total amount paid ($)" << endl;

        for (int i = 0; i < ps->getPayrollList().size(); i++) {
            Employee e = ps->getPayrollList()[i];
            stream << e.getEmployeeId() + "," + e.getFirstName() + "," + e.getLastName() + "," + e.getGender() + "," + e.getJobPosition() + "," + e.getStreetAddress() + "," + e.getCity() + "," + e.getState() + "," + e.getZipcode() + "," + QString::number(e.getNumberOfHours()) + "," + QString::number(e.getTotalNumberOfHours()) + "," + QString::number(e.getNumberOfOvertimeHours()) + "," + QString::number(e.getTotalNumberOfOvertimeHours()) + "," + QString::number(e.getHourlyWage()) + "," + QString::number(e.calcPay()) + "," + QString::number(e.getTotalAmountPaid())  << endl;
        }
    }

    file.close();

    mainLog->append(getCurrentTimeStamp() + " Saved the company '" + ps->getNameOfCompany() + "' in " + fileName + ".");
}

// Used for handling events when changing tabs (not implemented because don't have a purpose for it yet)
void CompanyTabWidget::tabChanged(int index)
{

}

// Used for removing employee
void CompanyTabWidget::removeEmployee()
{
    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }

    const QModelIndex &index = employeeTableView->currentIndex();
    const int row = employeeTableView->currentIndex().row();

    QString employeeId = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 0), Qt::DisplayRole).toString();

    ps->removeEmployeeById(employeeId);

    employeeTableView->tableViewModel->removeRowByRow(row);

    mainLog->append(getCurrentTimeStamp() + " Removed Employee #" + employeeId);

    update();
}

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qtcreator
// Used for adding employee
void CompanyTabWidget::toggleAddDialog() {
    CustomAddAndEditDialog *dialog = new CustomAddAndEditDialog();

    // Show the dialog as modal
    if (dialog->exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString employeeId = "E" + QString::number(id);
        QString firstName = dialog->firstNameLineEdit->text();
        QString lastName = dialog->lastNameLineEdit->text();
        QString gender = dialog->genderComboBox->currentText();
        QString jobPosition = dialog->jobPositionComboBox->currentText();
        QString streetAddress = dialog->streetAddressLineEdit->text();
        QString city = dialog->cityComboBox->currentText();
        QString state = dialog->stateComboBox->currentText();
        QString zipcode = dialog->zipcodeLineEdit->text();
        int numberOfHours = dialog->numberOfHoursLineEdit->text().toInt();
        int totalNumberOfHours = 0;
        int numberOfOvertimeHours =  0;
        int totalNumberOfOvertimeHours = 0;
        double hourlyWage = dialog->hourlyWageLineEdit->text().toDouble();
        double amountToBePaid = 0.00;
        double totalAmountPaid = 0.00;

        ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);
        employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);

        mainLog->append(getCurrentTimeStamp() + " Added Employee# " + employeeId);

        id++;

        update();
    }
}

// Used for editting employee
void CompanyTabWidget::toggleEditDialog() {
    if (timerButton->text().compare("Stop Timer") == 0) {
        toggleTimerButton();
    }

    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }
    const int row = employeeTableView->currentIndex().row();

    QString employeeId = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 0), Qt::DisplayRole).toString();
    QString oldFirstName = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 1), Qt::DisplayRole).toString();
    QString oldLastName = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 2), Qt::DisplayRole).toString();
    QString oldGender = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 3), Qt::DisplayRole).toString();
    QString oldPosition = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 4), Qt::DisplayRole).toString();
    QString oldStreet = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 5), Qt::DisplayRole).toString();
    QString oldCity = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 6), Qt::DisplayRole).toString();
    QString oldState = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 7), Qt::DisplayRole).toString();
    QString oldZipcode = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 8), Qt::DisplayRole).toString();
    int oldNumberOfHours = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 9), Qt::DisplayRole).toInt();
    double oldHourlyWage = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 13), Qt::DisplayRole).toDouble();

    CustomAddAndEditDialog *dialog = new CustomAddAndEditDialog();

    dialog->firstNameLineEdit->setText(oldFirstName);
    dialog->lastNameLineEdit->setText(oldLastName);
    dialog->genderComboBox->setCurrentText(oldGender);
    dialog->jobPositionComboBox->setCurrentText(oldPosition);
    dialog->streetAddressLineEdit->setText(oldStreet);
    dialog->cityComboBox->setCurrentText(oldCity);
    dialog->stateComboBox->setCurrentText(oldState);
    dialog->zipcodeLineEdit->setText(oldZipcode);
    dialog->numberOfHoursLineEdit->setText(QString::number(oldNumberOfHours));
    dialog->hourlyWageLineEdit->setText(QString::number(oldHourlyWage));

    // Show the dialog as modal
    if (dialog->exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString firstName = dialog->firstNameLineEdit->text();
        QString lastName = dialog->lastNameLineEdit->text();
        QString gender = dialog->genderComboBox->currentText();
        QString jobPosition = dialog->jobPositionComboBox->currentText();
        QString streetAddress = dialog->streetAddressLineEdit->text();
        QString city = dialog->cityComboBox->currentText();
        QString state = dialog->stateComboBox->currentText();
        QString zipcode = dialog->zipcodeLineEdit->text();
        int numberOfHours = dialog->numberOfHoursLineEdit->text().toInt();
        double hourlyWage = dialog->hourlyWageLineEdit->text().toDouble();

        ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        employeeTableView->tableViewModel->editRow(row, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        mainLog->append(getCurrentTimeStamp() + " Editted Employee# " + employeeId);

        update();
    }
}

// Updating labels in overview tab and graphs in statistics tab
void CompanyTabWidget::update() {
    nameOfCompanyLabel->setText("Company Name: " + ps->getNameOfCompany());
    nameOfCEOLabel->setText("Chief Executive Officer: " + ps->getCEO());
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount(), 'f', 2));
    companyBudgetLabel->setText("Budget: $" + QString::number(ps->getBudget(), 'f', 2));

    statsLayout->update();
}

// Used for loading csv files
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
    int numberOfHours = list[9].toInt();
    int totalNumberOfHours = list[10].toInt();
    int numberOfOvertimeHours = list[11].toInt();
    int totalNumberOfOvertimeHours = list[12].toInt();
    double hourlyWage = list[13].toDouble();
    double amountToBePaid = list[14].toDouble();
    double totalAmountPaid = list[15].toDouble();

    ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);
    employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, numberOfHours, totalNumberOfHours, numberOfOvertimeHours, totalNumberOfOvertimeHours, hourlyWage, amountToBePaid, totalAmountPaid);

    id++;
}

// Used for toggling timer with startTimer() and stopTimer(0 methods
void CompanyTabWidget::toggleTimerButton() {
    if (timerButton->text().compare("Start Timer") == 0) {
        startTimer();
        timerButton->setText("Stop Timer");
        mainLog->append(getCurrentTimeStamp() + " User pressed timer button. Timer was stopped.");
    }
    else {
        stopTimer();
        timerButton->setText("Start Timer");
        mainLog->append(getCurrentTimeStamp() + " User pressed timer button. Timer is resumed.");
    }
}

// Used for editting budget
void CompanyTabWidget::editBudget() {
    // Dialog to edit budget
    BudgetDialog *dialog = new BudgetDialog();
    dialog->budgetLineEdit->setText(QString::number(ps->getBudget(), 'f', 2));

    // Show the dialog as modal
    if (dialog->exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        double newBudget = dialog->budgetLineEdit->text().toDouble();
        mainLog->append(getCurrentTimeStamp() + " Editting company budget from $'" + QString::number(ps->getBudget(), 'f', 2) + "' to " + "'$" + QString::number(newBudget, 'f', 2) + "'.");
        ps->setBudget(newBudget);
        companyBudgetLabel->setText("Budget: $" + QString::number(ps->getBudget(), 'f', 2));
    }
}

// Used for paying employee
void CompanyTabWidget::payEmployee() {
    if (employeeTableView->currentIndex().isValid() == false) {
        return;
    }
    const int row = employeeTableView->currentIndex().row();

    QString employeeId = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 0), Qt::DisplayRole).toString();

    Employee e = ps->getEmployeeById(employeeId);

    double amount = e.calcPay();

    ps->payEmployeeById(e.getEmployeeId());

    employeeTableView->tableViewModel->payRowByRow(row);

    update();

    mainLog->append(getCurrentTimeStamp() + " Paid Employee #" + e.getEmployeeId() + " " + e.getFirstName() + " " + e.getLastName() + " in " + ps->getNameOfCompany() + " for $" + QString::number(amount, 'f', 2) + ".");
}

// Used for paying employees and updating employee table
void CompanyTabWidget::payAllEmployees() {
    if (timerButton->text().compare("Stop Timer") == 0) {
        toggleTimerButton();
    }

    ps->issuePaychecks();

    employeeTableView->tableViewModel->payAllRows();

    update();

    mainLog->append(getCurrentTimeStamp() + " Paid all employees in " + ps->getNameOfCompany() + ".");
}

// Used for logging
QString CompanyTabWidget::getCurrentTimeStamp() const {
    QString timestamp = "[" + QDateTime::currentDateTime().toString() + "]";
    return timestamp;
}
