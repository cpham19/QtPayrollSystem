#include "headers/globals.h"

int counter = 0;
vector<QString> maleFirstNames;
vector<QString> femaleFirstNames;
vector<QString> lastNames;
vector<QString> jobs;
vector<QString> streets;
vector<QString> streetSuffixes;
vector<QString> cities;
vector<QString> states;
vector<QString> zipcodes;

vector<int> months{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
vector<int> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
vector<int> hours{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
//    vector<int> minutes{1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
//                        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
//                        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
//                        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
//                        41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
//                        51, 52, 53, 54, 55, 56, 57, 58, 59};
vector<QString> meridiems{"AM", "PM"};

vector<QString> monthStrings{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

QTextEdit *mainLog;
