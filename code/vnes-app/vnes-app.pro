TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG += qt
QT += network core widgets

SOURCES += \
        controller.cpp \
        main.cpp \
        mainwindow.cpp \
        networkhandler.cpp \
        utils.cpp

HEADERS += \
    controller.h \
    mainwindow.h \
    networkhandler.h \
    utils.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    media.qrc
