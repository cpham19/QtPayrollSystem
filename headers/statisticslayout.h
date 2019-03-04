#ifndef STATISTICSLAYOUT_H
#define STATISTICSLAYOUT_H

#include <QJsonObject>
#include <QColor>
#include <QAbstractBarSeries>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>

#include "payrollsystem.h"

class StatisticsLayout : public QVBoxLayout
{
    Q_OBJECT

public:
    StatisticsLayout(PayrollSystem *payrollSystem, QWidget *parent = nullptr);

    void createStackedWidget();
    void createGenderWidget();
    void createPositionWidget();
    void createAverageSalaryWidget();
    void update();

    // Statistics Tab
    QStackedWidget *stackedWidget;
    QWidget *positionWidget;
    QWidget *genderWidget;
    QWidget *averageSalariesWidget;
    QComboBox *statsComboBox;

    QVBoxLayout *genderLayout;
    QPieSeries *genderSeries;
    QChart *genderChart;
    QChartView *genderChartView;

    QVBoxLayout *positionLayout;
    QPieSeries *positionSeries;
    QChart *positionChart;
    QChartView *positionChartView;

    QVBoxLayout *averageSalariesLayout;
    QBarSeries *averageSalariesSeries;
    QChart *averageSalariesChart;
    QChartView *averageSalariesChartView;
    QBarCategoryAxis *axisX;
    QValueAxis *axisY;

    PayrollSystem *ps;

signals:

public slots:

private slots:


protected:

};


#endif // STATISTICSLAYOUT_H
