TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += qt
QT += network core widgets

SOURCES += \
        apicalls.cpp \
        main.cpp

HEADERS += \
    apicalls.hh
