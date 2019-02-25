#include "headers/companytabwidget.h"
#include "headers/globals.h"

CompanyTabWidget::CompanyTabWidget(QWidget *parent, QString name): QTabWidget(parent) {
    initializeData(name);
    createOverviewTab();
    createEmployeeTableTab();
    createStatisticsTab();
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

    this->setStyleSheet("QTabBar::tab { height: 25px; width: 300px;}");
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
    uniform_int_distribution<int> *jobsDistribution = new uniform_int_distribution<int>(0, jobs.size() - 1);
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
        double hourlyWage = QString::number(doubleDistribution(generator), 'f', 2).toDouble();
        int numberOfHours =  numberOfEmployeesDistribution(generator);

        ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);
        employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);

        id++;
    }

    if (ps->containCEO() == false) {
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

        QString position = "Chief Executive Officer";
        QString street = streets[streetsDistribution(generator)] + " " + streetSuffixes[streetSuffixesDistribution(generator)];
        QString city = cities[citiesDistribution(generator)];
        QString state = states[statesDistribution(generator)];
        QString zipcode = zipcodes[zipcodesDistribution(generator)];
        double hourlyWage = QString::number(doubleDistribution(generator), 'f', 2).toDouble();
        int numberOfHours =  numberOfEmployeesDistribution(generator);

        ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);
        employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);

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
    this->addTab(overviewGroupBox, "Overview");
}

void CompanyTabWidget::createEmployeeTableTab() {
    tableGroupBox = new QGroupBox("List of Employees");
    tableLayout = new QGridLayout();

    employeeTableView = new EmployeeTableView(ps);

    addButton = new QPushButton("Add");
    generateEmployeesButton = new QPushButton("Generate Employees");
    removeButton = new QPushButton("Remove");
    payAllButton = new QPushButton("Pay All");
    timerButton = new QPushButton("Stop Timer");

    connect(addButton, SIGNAL (clicked()), SLOT (toggleAddDialog()));
    connect(employeeTableView,SIGNAL(doubleClicked(const QModelIndex&)), SLOT (toggleEditDialog()));
    connect(generateEmployeesButton, SIGNAL (clicked()), SLOT(generateRandomEmployees()));
    connect(removeButton, SIGNAL (clicked()), SLOT (removeEmployee()));
    connect(payAllButton, SIGNAL (clicked()), SLOT (payAllEmployees()));
    connect(timerButton, SIGNAL (clicked()), SLOT (toggleTimerButton()));

    tableLayout->addWidget(employeeTableView, 0, 0, 10, 5);
    tableLayout->addWidget(addButton, 11, 0);
    tableLayout->addWidget(generateEmployeesButton, 11, 1);
    tableLayout->addWidget(removeButton, 11, 2);
    tableLayout->addWidget(payAllButton, 11, 3);
    tableLayout->addWidget(timerButton, 11, 4);

    tableGroupBox->setLayout(tableLayout);
    this->addTab(tableGroupBox, "Employees");
}

void CompanyTabWidget::createStatisticsTab() {
    statsGroupBox = new QGroupBox("Stats");
    stackedWidget = new QStackedWidget;
    genderWidget = new QWidget;
    positionWidget = new QWidget;
    averageSalariesWidget = new QWidget;

    stackedWidget->addWidget(genderWidget);
    stackedWidget->addWidget(positionWidget);
    stackedWidget->addWidget(averageSalariesWidget);

    statsLayout = new QVBoxLayout();
    genderLayout = new QVBoxLayout();
    positionLayout = new QVBoxLayout();
    averageSalariesLayout = new QVBoxLayout();

    statsComboBox = new QComboBox;
    statsComboBox->addItem(tr("Gender Pie Chart"));
    statsComboBox->addItem(tr("Position Pie Chart"));
    statsComboBox->addItem(tr("Average Salary Bar Chart"));
    connect(statsComboBox, SIGNAL(activated(int)), stackedWidget, SLOT(setCurrentIndex(int)));

    genderSeries = new QPieSeries();
    genderSeries->setHoleSize(0.10);

    QJsonObject genderObj = ps->getNumberOfGenders();

    foreach(const QString& key, genderObj.keys()) {
        int value = genderObj.value(key).toInt();
        QPieSlice *slice = genderSeries->append(key + " " + QString::number(value), value);
        slice->setExploded();
        slice->setExplodeDistanceFactor(0.10);
        slice->setLabelVisible();
    }

    genderChart = new QChart();
    genderChart->setTitle("Number of Males and Females in the Company");
    genderChart->addSeries(genderSeries);
    genderChart->setTheme(QChart::ChartThemeBlueCerulean);
    genderChart->legend()->setFont(QFont("Arial", 7));
    genderChart->legend()->setAlignment(Qt::AlignRight);
    //genderChart->legend()->hide();

    genderChartView = new QChartView(genderChart);
    //genderChartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    genderChartView->setRenderHint(QPainter::Antialiasing);

    genderLayout->addWidget(genderChartView);
    genderWidget->setLayout(genderLayout);

    positionSeries = new QPieSeries();
    positionSeries->setHoleSize(0.10);

    QJsonObject positionObj = ps->getNumberOfPeopleWithPositions();

    foreach(const QString& key, positionObj.keys()) {
        int value = positionObj.value(key).toInt();
        QPieSlice *slice = positionSeries->append(key + " " + QString::number(value), value);
        slice->setExploded();
        slice->setExplodeDistanceFactor(0.10);
        slice->setLabelVisible();
    }

    positionChart = new QChart();
    positionChart->setTitle("Number of People in Job Positions");
    positionChart->addSeries(positionSeries);
    positionChart->setTheme(QChart::ChartThemeBlueCerulean);
    positionChart->legend()->setAlignment(Qt::AlignRight);
    positionChart->legend()->setFont(QFont("Arial", 7));
    //positionChart->legend()->hide();

    positionChartView = new QChartView(positionChart);
    positionChartView->setRenderHint(QPainter::Antialiasing);
    //positionChartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    positionLayout->addWidget(positionChartView);
    positionWidget->setLayout(positionLayout);

    averageSalariesSeries = new QBarSeries();
    averageSalariesSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideEnd);
    //averageSalariesSeries->setLabelsAngle(270);
    averageSalariesSeries->setLabelsFormat("$@value");
    averageSalariesSeries->setLabelsVisible(true);
    averageSalariesSeries->setBarWidth(0.8);

    averageSalariesChart = new QChart();
    averageSalariesChart->addSeries(averageSalariesSeries);
    averageSalariesChart->setTitle("Average Salaries of Job Positions");
    averageSalariesChart->setAnimationOptions(QChart::SeriesAnimations);
    averageSalariesChart->legend()->setAlignment(Qt::AlignBottom);
    averageSalariesChart->legend()->hide();

    QStringList categories;
    QBarSet *set = new QBarSet("");
    QJsonObject salariesObj = ps->getAverageSalariesOfPositions();
    foreach(const QString& key, salariesObj.keys()) {
        double averageSalary = salariesObj.value(key).toDouble();
        categories.append(key);
        set->append(averageSalary);
    }

    axisX = new QBarCategoryAxis();
    axisX->setTitleText("Job Positions");
    axisX->setTitleVisible(true);

    averageSalariesSeries->append(set);
    if (categories.size() != 0) {
        axisX->append(categories);
        axisX->setRange(categories[0], categories[categories.size() - 1]);
    }

    averageSalariesChart->addAxis(axisX, Qt::AlignBottom);
    averageSalariesSeries->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setTitleText("Average Salary ($)");
    axisY->setTitleVisible(true);
    axisY->setRange(0,150000.00);
    averageSalariesChart->addAxis(axisY, Qt::AlignLeft);
    averageSalariesSeries->attachAxis(axisY);

    averageSalariesChartView = new QChartView(averageSalariesChart);
    averageSalariesChartView->setRenderHint(QPainter::Antialiasing);
    //averageSalariesChartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    averageSalariesChartView->setRubberBand(QChartView::HorizontalRubberBand);
    averageSalariesChartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    averageSalariesChartView->setDragMode(QGraphicsView::ScrollHandDrag);

    averageSalariesLayout->addWidget(averageSalariesChartView);
    averageSalariesWidget->setLayout(averageSalariesLayout);

    statsLayout->addWidget(statsComboBox);
    statsLayout->addWidget(stackedWidget);
    statsGroupBox->setLayout(statsLayout);

    this->addTab(statsGroupBox, "Statistics");
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

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), qApp->applicationDirPath() + "/csv/" + ps->getNameOfCompany() + ".csv", tr("Comma-separated Values File (*.csv)"));
    QFile file(fileName);
    file.remove();

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "name of company,number of employees,amount paid ($)" << endl;
        stream << ps->getNameOfCompany() + "," + QString::number(ps->getPayrollList().size()) + "," + QString::number(ps->getTotalAmount()) << endl;
        stream << endl << endl;

        stream << "employee id,first name,last name,gender,job position,street address,city,state,zipcode,hourly wage,hours worked,amount to be paid ($),total amount of hours worked,total amount paid ($)" << endl;

        for (int i = 0; i < ps->getPayrollList().size(); i++) {
            Employee e = ps->getPayrollList()[i];
            stream << e.getEmployeeId() + "," + e.getFirstName() + "," + e.getLastName() + "," + e.getGender() + "," + e.getJobPosition() + "," + e.getStreetAddress() + "," + e.getCity() + "," + e.getState() + "," + e.getZipcode() + "," + QString::number(e.getHourlyWage()) + "," + QString::number(e.getNumberOfHours()) + "," + QString::number(e.getHourlyWage() * e.getNumberOfHours()) + "," + QString::number(e.getTotalNumberOfHours()) + "," + QString::number(e.getTotalAmountPaid())  << endl;
        }
    }

    file.close();

    mainLog->append(getCurrentTimeStamp() + " Saved the company '" + ps->getNameOfCompany() + "' in " + fileName + ".");

    createTimer();
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

    QString employeeId = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 0), Qt::DisplayRole).toString();

    ps->removeEmployeeById(employeeId);

    employeeTableView->tableViewModel->removeRowByRow(employeeId, row);

    mainLog->append(getCurrentTimeStamp() + " Removed Employee #" + employeeId);

    update();
}

// https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qtcreator
void CompanyTabWidget::toggleAddDialog() {
    stopTimer();

    CustomDialog dialog(this);

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString employeeId = "E" + QString::number(id);
        QString firstName = dialog.firstNameLineEdit->text();
        QString lastName = dialog.lastNameLineEdit->text();
        QString gender = dialog.genderComboBox->currentText();
        QString jobPosition = dialog.jobPositionComboBox->currentText();
        QString streetAddress = dialog.streetAddressLineEdit->text();
        QString city = dialog.cityComboBox->currentText();
        QString state = dialog.stateComboBox->currentText();
        QString zipcode = dialog.zipcodeLineEdit->text();
        double hourlyWage = dialog.hourlyWageLineEdit->text().toDouble();
        int numberOfHours = dialog.numberOfHoursLineEdit->text().toInt();

        ps->addEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);
        employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours, 0.00, 0);

        mainLog->append(getCurrentTimeStamp() + " Added Employee# " + employeeId);

        id++;

        update();
    }

    createTimer();
}

void CompanyTabWidget::toggleEditDialog() {
    stopTimer();

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
    double oldHourlyWage = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 9), Qt::DisplayRole).toDouble();
    int oldNumberOfHours = employeeTableView->tableViewModel->data(employeeTableView->tableViewModel->index(row, 10), Qt::DisplayRole).toInt();

    CustomDialog dialog(this);

    dialog.firstNameLineEdit->setText(oldFirstName);
    dialog.lastNameLineEdit->setText(oldLastName);
    dialog.genderComboBox->setCurrentText(oldGender);
    dialog.jobPositionComboBox->setCurrentText(oldPosition);
    dialog.streetAddressLineEdit->setText(oldStreet);
    dialog.cityComboBox->setCurrentText(oldCity);
    dialog.stateComboBox->setCurrentText(oldState);
    dialog.zipcodeLineEdit->setText(oldZipcode);
    dialog.hourlyWageLineEdit->setText(QString::number(oldHourlyWage));
    dialog.numberOfHoursLineEdit->setText(QString::number(oldNumberOfHours));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        QString firstName = dialog.firstNameLineEdit->text();
        QString lastName = dialog.lastNameLineEdit->text();
        QString gender = dialog.genderComboBox->currentText();
        QString jobPosition = dialog.jobPositionComboBox->currentText();
        QString streetAddress = dialog.streetAddressLineEdit->text();
        QString city = dialog.cityComboBox->currentText();
        QString state = dialog.stateComboBox->currentText();
        QString zipcode = dialog.zipcodeLineEdit->text();
        double hourlyWage = dialog.hourlyWageLineEdit->text().toDouble();
        int numberOfHours = dialog.numberOfHoursLineEdit->text().toInt();

        ps->editEmployee(employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        employeeTableView->tableViewModel->editRow(row, employeeId, firstName, lastName, gender, jobPosition, streetAddress, city, state, zipcode, hourlyWage, numberOfHours);

        mainLog->append(getCurrentTimeStamp() + " Editted Employee# " + employeeId);

        update();
    }

    createTimer();
}

void CompanyTabWidget::update() {
    nameOfCompanyLabel->setText("Company Name: " + ps->getNameOfCompany());
    nameOfCEOLabel->setText("Chief Executive Officer: " + ps->getCEO());
    numberOfEmployeesLabel->setText("Number of Employees: " + QString::number((int) ps->getPayrollList().size()));
    totalAmountPaidLabel->setText("Total Amount Paid: $" + QString::number(ps->getTotalAmount(), 'f', 2));

    genderSeries->clear();
    QJsonObject genderObj = ps->getNumberOfGenders();
    qDebug() << genderObj;
    foreach(const QString& key, genderObj.keys()) {
        int value = genderObj.value(key).toInt();
        QPieSlice *slice = genderSeries->append(key + " " + QString::number(value), value);
        slice->setExploded();
        slice->setExplodeDistanceFactor(0.10);
        slice->setLabelVisible();
    }

    positionSeries->clear();
    QJsonObject obj = ps->getNumberOfPeopleWithPositions();

    foreach(const QString& key, obj.keys()) {
        int value = obj.value(key).toInt();
        QPieSlice *slice = positionSeries->append(key + " " + QString::number(value), value);
        slice->setExploded();
        slice->setExplodeDistanceFactor(0.10);
        slice->setLabelVisible();
    }

    QStringList categories;
    averageSalariesSeries->clear();

    QBarSet *set = new QBarSet("");
    QJsonObject salariesObj = ps->getAverageSalariesOfPositions();
    foreach(const QString& key, salariesObj.keys()) {
        double averageSalary = salariesObj.value(key).toDouble();
        categories.append(key);
        set->append(QString::number(averageSalary, 'f', 2).toDouble());
    }

    averageSalariesSeries->append(set);
    axisX->append(categories);
    axisX->setRange(categories[0], categories[categories.size() - 1]);
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
    int totalNumberOfHours = list[12].toInt();
    double totalAmountPaid = list[13].toDouble();


    ps->addEmployee(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, totalAmountPaid, totalNumberOfHours);
    employeeTableView->tableViewModel->insertNewRow(employeeId, firstName, lastName, gender, position, street, city, state, zipcode, hourlyWage, numberOfHours, totalAmountPaid, totalNumberOfHours);

    id++;
}

void CompanyTabWidget::toggleTimerButton() {
    if (timerButton->text().compare("Start Timer") == 0) {
        createTimer();
        timerButton->setText("Stop Timer");
        mainLog->append(getCurrentTimeStamp() + " User pressed timer button. Timer was stopped.");
    }
    else {
        stopTimer();
        timerButton->setText("Start Timer");
        mainLog->append(getCurrentTimeStamp() + " User pressed timer button. Timer is resumed.");
    }
}

void CompanyTabWidget::payAllEmployees() {
    stopTimer();

    ps->issuePaychecks();

    employeeTableView->tableViewModel->payAllRows();

    update();

    mainLog->append(getCurrentTimeStamp() + " Paid all employees in " + ps->getNameOfCompany() + ".");

    createTimer();
}

void CompanyTabWidget::timerEvent(QTimerEvent *event)
{
    ps->incrementHoursOfEmployees();

    employeeTableView->tableViewModel->incrementHours();

    //update();
}

QString CompanyTabWidget::getCurrentTimeStamp() const {
    QString timestamp = "[" + QDateTime::currentDateTime().toString() + "]";
    return timestamp;
}
