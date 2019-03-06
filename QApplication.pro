#-------------------------------------------------
#
# Project created by QtCreator 2019-01-09T18:48:53
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QApplication
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/employee.cpp \
    sources/paycheck.cpp \
    sources/payrollsystem.cpp \
    sources/companytabwidget.cpp \
    sources/globals.cpp \
    sources/employeetablemodel.cpp \
    sources/customdialog.cpp \
    sources/employeetableview.cpp \
    sources/digitalclock.cpp \
    sources/statisticslayout.cpp \
    sources/budgetdialog.cpp

HEADERS += \
    headers/mainwindow.h \
    headers/employee.h \
    headers/paycheck.h \
    headers/payrollsystem.h \
    headers/companytabwidget.h \
    headers/globals.h \
    headers/employeetablemodel.h \
    headers/customdialog.h \
    headers/employeetableview.h \
    headers/digitalclock.h \
    headers/statisticslayout.h \
    headers/budgetdialog.h

FORMS += \
        mainwindow.ui
		
OTHER_FILES += \
        txt/firstnames.txt \
        txt/lastnames.txt \
        txt/jobs.txt \
        txt/streets.txt \
        txt/streetsuffixes.txt \
        txt/cities.txt \
        txt/states.txt \
        txt/zipcodes.txt
	

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
