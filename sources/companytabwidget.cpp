#include "headers/companytabwidget.h"
#include "headers/globals.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent, QString name): QTabWidget(parent) {
    initializeData(name);
    createOverviewTab();
    createEmployeeTab();
    createEmployeeTableTab();
    createPayrollTab();

    timerId = startTimer(1000);
}

CompanyTabWidget::~CompanyTabWidget()
{
    killTimer(timerId);
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
        mt19937 generator2(rand());
        QString id = "E" + QString::number(i);
        QString gender;
        QString firstName;

        if ((int) genderDistribution(generator2) == 0 ) {
            gender = "Male";
            firstName = maleFirstNames[maleFirstNamesDistribution(generator2)];
        }
        else {
            gender = "Female";
            firstName = femaleFirstNames[femaleFirstNamesDistribution(generator2)];
        }

        QString lastName = lastNames[lastNamesDistribution(generator2)];
        QString position = jobs[jobsDistribution(generator2)];
        QString street = streets[streetsDistribution(generator2)] + " " + streetSuffixes[streetSuffixesDistribution(generator)];
        QString city = cities[citiesDistribution(generator2)];
        QString state = states[statesDistribution(generator2)];
        QString zipcode = zipcodes[zipcodesDistribution(generator2)];
        double hourlyWage = doubleDistribution(generator2);
        int numberOfHours =  numberOfEmployeesDistribution(generator2);

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

void CompanyTabWidget::createEmployeeTab() {
    employeeGroupBox = new QGroupBox(tr("Add, Edit, or Remove Employee"));
    employeeLayout = new QGridLayout();

    setUpEmployeeInputs();
    setUpValidators();
    setUpEmployeeListView();

    employeeGroupBox->setLayout(employeeLayout);

    connect(this, SIGNAL(currentChanged(int)), SLOT(tabChanged(int)));
    this->addTab(employeeGroupBox, "CRUD");
}

void CompanyTabWidget::createEmployeeTableTab() {
    tableGroupBox = new QGroupBox("List of Employees");
    QGridLayout *tableLayout = new QGridLayout();

    setUpEmployeeTable();

    tableLayout->addWidget(employeeTableView);
    tableGroupBox->setLayout(tableLayout);
    this->addTab(tableGroupBox, "Employees");
}

void CompanyTabWidget::createPayrollTab() {
    payrollGroupBox = new QGroupBox("Paychecks");
    QGridLayout *tableLayout = new QGridLayout();

    setUpPayrollTable();

    payButton = new QPushButton("Pay all");
    connect(payButton, SIGNAL (clicked()), SLOT (payEmployees()));

    tableLayout->addWidget(payrollTableView);
    tableLayout->addWidget(payButton);
    payrollGroupBox->setLayout(tableLayout);
    this->addTab(payrollGroupBox, "Payroll");
}

void CompanyTabWidget::setUpEmployeeInputs() {
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

    addButton = new QPushButton("Add");
    connect(addButton, SIGNAL (clicked()), SLOT (addEmployee()));

    editButton = new QPushButton("Edit");
    connect(editButton, SIGNAL (clicked()), SLOT (editEmployee()));

    removeButton = new QPushButton("Remove");
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));

    clearButton = new QPushButton("Clear form");
    connect(clearButton, SIGNAL (clicked()), SLOT (clearForms()));

    buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(removeButton);

    employeeLayout->addLayout(buttonLayout, 10, 0, 1, 2);
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

    listViewModel->insertRow(listViewModel->rowCount());
    QModelIndex index = listViewModel->index(listViewModel->rowCount()-1);
    QString employee = employeeId + " " + firstName + " " + lastName;
    listViewModel->setData(index, employee);

    clearForms();
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

void CompanyTabWidget::setUpEmployeeListView() {
    employeeListView = new QListView();

    employeeListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(employeeListView, SIGNAL(clicked(QModelIndex)), this, SLOT(employeeListViewClicked(QModelIndex)));

    QStringList list = ps->getEmployeesStringList();
    listViewModel = new EmployeeStringListModel(list);
    employeeListView->setModel(listViewModel);

    // 0 is the starting row, 4 is the starting column, 10 is the length (top to bottom), 8 is width (left to right)
    employeeLayout->addWidget(employeeListView, 0, 4, 10, 8);
}

void CompanyTabWidget::setUpEmployeeTable() {
    employeeTableView = new QTableView();
    employeeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    employeeTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    vector<Employee> list = ps->getPayrollList();
    tableViewModel = new EmployeeTableModel(list);
    employeeTableView->setModel(tableViewModel);
}

void CompanyTabWidget::setUpPayrollTable() {
    payrollTableView = new QTableView();
    payrollTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    payrollTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    vector<Employee> list = ps->getPayrollList();
    payrollViewModel = new PayrollTableModel(list);
    payrollTableView->setModel(payrollViewModel);
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
    const int row = employeeListView->currentIndex().row();
    QString employeeText = index.data(Qt::DisplayRole).toString();
    QString employeeId = (employeeText.split(QRegExp("\\s+"), QString::SkipEmptyParts))[0];

    ps->removeEmployeeById(employeeId);

    listViewModel->removeRow(row, index);


    const QModelIndex &newIndex = employeeListView->currentIndex();
    employeeText = newIndex.data(Qt::DisplayRole).toString();
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

void CompanyTabWidget::editEmployee()
{
    if (employeeListView->currentIndex().isValid() == false) {
        return;
    }
    const QModelIndex &index = employeeListView->currentIndex();
    const int row = employeeListView->currentIndex().row();
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

    QString employee = employeeId + " " + firstName + " " + lastName;
    listViewModel->setData(index, employee);
}

void CompanyTabWidget::update() {
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount()));

    //    tableViewModel = ps->getEmployeesModel();
    //    employeeTableView->setModel(tableViewModel);

    //    payrollViewModel = ps->getPaychecksModel();
    //    payrollTableView->setModel(payrollViewModel);
}

void CompanyTabWidget::payEmployees() {
    ps->issuePaychecks();
    update();
}

void CompanyTabWidget::timerEvent(QTimerEvent *event)
{
//    ps->incrementHoursOfEmployees();
//    update();
}
