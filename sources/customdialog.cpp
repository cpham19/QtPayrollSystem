#include "headers/customdialog.h"
#include "headers/globals.h"

CustomAddAndEditDialog::CustomAddAndEditDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Employee");
    setupInputs();
    setupValidators();
}

// Used for creating the form itself
void CustomAddAndEditDialog::setupInputs() {
    // Use a layout allowing to have a label next to each field
    QFormLayout *form = new QFormLayout(this);

    firstNameLabel = new QLabel();
    firstNameLabel->setText("First Name");
    firstNameLineEdit = new QLineEdit(this);

    lastNameLabel = new QLabel();
    lastNameLabel->setText("Last Name");
    lastNameLineEdit = new QLineEdit(this);

    genderComboBoxLabel = new QLabel();
    genderComboBoxLabel->setText("Gender");
    genderComboBox = new QComboBox(this);
    genderComboBox->addItem("Male");
    genderComboBox->addItem("Female");

    jobPositionLabel = new QLabel();
    jobPositionLabel->setText("Job Position");
    jobPositionComboBox = new QComboBox(this);
    for (QString position : jobs) {
        jobPositionComboBox->addItem(position);
    }

    streetAddressLabel = new QLabel();
    streetAddressLabel->setText("Street Address");
    streetAddressLineEdit = new QLineEdit(this);

    cityLabel = new QLabel();
    cityLabel->setText("City");
    cityComboBox = new QComboBox(this);
    for (QString city : cities) {
        cityComboBox->addItem(city);
    }

    stateLabel = new QLabel();
    stateLabel->setText("State");
    stateComboBox = new QComboBox(this);
    for (QString state : states) {
        stateComboBox->addItem(state);
    }

    zipcodeLabel = new QLabel();
    zipcodeLabel->setText("Zipcode");
    zipcodeLineEdit = new QLineEdit(this);

    hourlyWageLabel = new QLabel();
    hourlyWageLabel->setText("Hourly Wage");
    hourlyWageLineEdit = new QLineEdit(this);

    numberOfHoursLabel = new QLabel();
    numberOfHoursLabel->setText("Number of hours worked");
    numberOfHoursLineEdit = new QLineEdit(this);

    form->addRow(firstNameLabel, firstNameLineEdit);
    form->addRow(lastNameLabel, lastNameLineEdit);
    form->addRow(genderComboBoxLabel, genderComboBox);
    form->addRow(jobPositionLabel, jobPositionComboBox);
    form->addRow(streetAddressLabel, streetAddressLineEdit);
    form->addRow(cityLabel, cityComboBox);
    form->addRow(stateLabel, stateComboBox);
    form->addRow(zipcodeLabel, zipcodeLineEdit);
    form->addRow(hourlyWageLabel, hourlyWageLineEdit);
    form->addRow(numberOfHoursLabel, numberOfHoursLineEdit);

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, this);

    QPushButton *autofillButton = new QPushButton("Autofill forms");
    connect(autofillButton, SIGNAL (clicked()), SLOT (automaticallyFill()));
    buttonBox->addButton(autofillButton, QDialogButtonBox::ActionRole);

    form->addRow(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

// Used for data input validation
void CustomAddAndEditDialog::setupValidators() {
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

// Used for autofilling fields (if user is lazy)
void CustomAddAndEditDialog::automaticallyFill() {
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
