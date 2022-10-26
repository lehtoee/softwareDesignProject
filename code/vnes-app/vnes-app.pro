TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += qt
QT += network core widgets

SOURCES += \
        apicalls.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    apicalls.hh \
    mainwindow.h

FORMS += \
    mainwindow.ui
