#include "headers/statisticslayout.h"

StatisticsLayout::StatisticsLayout(PayrollSystem *payrollSystem, QWidget *parent): ps(payrollSystem), QVBoxLayout(parent) {
    createGenderWidget();
    createPositionWidget();
    createAverageSalaryWidget();
    createStackedWidget();
}

void StatisticsLayout::createStackedWidget() {
    stackedWidget = new QStackedWidget;

    stackedWidget->addWidget(genderWidget);
    stackedWidget->addWidget(positionWidget);
    stackedWidget->addWidget(averageSalariesWidget);

    statsComboBox = new QComboBox;
    statsComboBox->addItem(tr("Gender Pie Chart"));
    statsComboBox->addItem(tr("Position Pie Chart"));
    statsComboBox->addItem(tr("Average Salary Bar Chart"));
    connect(statsComboBox, SIGNAL(activated(int)), stackedWidget, SLOT(setCurrentIndex(int)));

    this->addWidget(statsComboBox);
    this->addWidget(stackedWidget);
}



void StatisticsLayout::createGenderWidget() {
    genderWidget = new QWidget;
    genderLayout = new QVBoxLayout();

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
}

void StatisticsLayout::createPositionWidget() {
    positionWidget = new QWidget;

    positionLayout = new QVBoxLayout();

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
}

void StatisticsLayout::createAverageSalaryWidget() {
    averageSalariesWidget = new QWidget;

    averageSalariesLayout = new QVBoxLayout();

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
}

void StatisticsLayout::update() {
    genderSeries->clear();
    QJsonObject genderObj = ps->getNumberOfGenders();
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
