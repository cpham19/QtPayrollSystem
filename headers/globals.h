#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <QString>
#include <QTextEdit>

using namespace std;

extern vector<QString> maleFirstNames;
extern vector <QString> femaleFirstNames;
extern vector<QString> lastNames;
extern vector<QString> jobs;
extern vector<QString> streets;
extern vector<QString> streetSuffixes;
extern vector<QString> cities;
extern vector<QString> zipcodes;
extern vector<QString> states;

extern vector<int> hours;
extern vector<int> minutes;
extern vector<QString> meridiems;

extern vector<int> days;
extern vector<int> months;
extern vector<QString> monthStrings;
extern vector<int> years;

extern QTextEdit *mainLog;

extern int counter;

#endif // GLOBALS_H
