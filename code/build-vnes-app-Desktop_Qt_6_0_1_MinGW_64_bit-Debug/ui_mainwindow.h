/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *locationLabel;
    QLabel *timelineLabel;
    QLabel *datatypeLabel;
    QComboBox *locationDropDown;
    QComboBox *timelineDropDown;
    QComboBox *datatypeDropDown;
    QLabel *dataLabel;
    QGraphicsView *graphicsView;
    QPushButton *fetchDataButton;
    QPushButton *weatherButton;
    QPushButton *trafficButton;
    QPushButton *combinedButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(863, 625);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        locationLabel = new QLabel(centralwidget);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));
        locationLabel->setGeometry(QRect(260, 150, 121, 31));
        QFont font;
        font.setPointSize(16);
        locationLabel->setFont(font);
        timelineLabel = new QLabel(centralwidget);
        timelineLabel->setObjectName(QString::fromUtf8("timelineLabel"));
        timelineLabel->setGeometry(QRect(260, 250, 151, 31));
        timelineLabel->setFont(font);
        datatypeLabel = new QLabel(centralwidget);
        datatypeLabel->setObjectName(QString::fromUtf8("datatypeLabel"));
        datatypeLabel->setGeometry(QRect(260, 350, 171, 31));
        datatypeLabel->setFont(font);
        locationDropDown = new QComboBox(centralwidget);
        locationDropDown->setObjectName(QString::fromUtf8("locationDropDown"));
        locationDropDown->setGeometry(QRect(260, 190, 231, 41));
        timelineDropDown = new QComboBox(centralwidget);
        timelineDropDown->setObjectName(QString::fromUtf8("timelineDropDown"));
        timelineDropDown->setGeometry(QRect(260, 290, 231, 41));
        datatypeDropDown = new QComboBox(centralwidget);
        datatypeDropDown->setObjectName(QString::fromUtf8("datatypeDropDown"));
        datatypeDropDown->setGeometry(QRect(260, 390, 231, 41));
        dataLabel = new QLabel(centralwidget);
        dataLabel->setObjectName(QString::fromUtf8("dataLabel"));
        dataLabel->setGeometry(QRect(260, 50, 351, 52));
        dataLabel->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setPointSize(32);
        dataLabel->setFont(font1);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(540, 130, 300, 300));
        graphicsView->setMaximumSize(QSize(300, 300));
        fetchDataButton = new QPushButton(centralwidget);
        fetchDataButton->setObjectName(QString::fromUtf8("fetchDataButton"));
        fetchDataButton->setGeometry(QRect(20, 440, 200, 100));
        fetchDataButton->setMaximumSize(QSize(200, 100));
        fetchDataButton->setIconSize(QSize(100, 100));
        weatherButton = new QPushButton(centralwidget);
        weatherButton->setObjectName(QString::fromUtf8("weatherButton"));
        weatherButton->setGeometry(QRect(20, 200, 200, 100));
        weatherButton->setMaximumSize(QSize(200, 100));
        weatherButton->setIconSize(QSize(100, 100));
        weatherButton->setCheckable(true);
        trafficButton = new QPushButton(centralwidget);
        trafficButton->setObjectName(QString::fromUtf8("trafficButton"));
        trafficButton->setGeometry(QRect(20, 70, 200, 100));
        trafficButton->setMaximumSize(QSize(200, 100));
        trafficButton->setAutoFillBackground(false);
        trafficButton->setIconSize(QSize(100, 100));
        trafficButton->setCheckable(true);
        combinedButton = new QPushButton(centralwidget);
        combinedButton->setObjectName(QString::fromUtf8("combinedButton"));
        combinedButton->setGeometry(QRect(20, 320, 200, 100));
        combinedButton->setMaximumSize(QSize(200, 100));
        combinedButton->setBaseSize(QSize(0, 0));
        combinedButton->setIconSize(QSize(100, 100));
        combinedButton->setCheckable(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 863, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        locationLabel->setText(QCoreApplication::translate("MainWindow", "Set location: ", nullptr));
        timelineLabel->setText(QCoreApplication::translate("MainWindow", "Select timeline:", nullptr));
        datatypeLabel->setText(QCoreApplication::translate("MainWindow", "Select Datatype:", nullptr));
        dataLabel->setText(QCoreApplication::translate("MainWindow", "Traffic Data", nullptr));
        fetchDataButton->setText(QCoreApplication::translate("MainWindow", "Fetch Data", nullptr));
        weatherButton->setText(QCoreApplication::translate("MainWindow", "Weather Data", nullptr));
        trafficButton->setText(QCoreApplication::translate("MainWindow", "Traffic Data", nullptr));
        combinedButton->setText(QCoreApplication::translate("MainWindow", "Combined Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
