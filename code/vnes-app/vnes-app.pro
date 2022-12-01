TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += qt
QT += network core widgets

SOURCES += \
        controller.cpp \
        main.cpp \
        mainwindow.cpp \
        networkhandler.cpp

HEADERS += \
    controller.h \
    mainwindow.h \
    networkhandler.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    media.qrc
