#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "networkhandler.h"
#include "mainwindow.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <map>
#include <QFile>
#include <iostream>
#include <unordered_map>
#include <QJsonArray>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(NetworkHandler* networkhandler, MainWindow* view);
    ~Controller();

    void pushButtonClicked(QString source, QString datatype,
                           QString location, QString time);
    void createDigiTrafficChart(std::unordered_map<QString, QString> data, QString datatype);
    void createFMIChart(std::unordered_map<QString, std::vector<double>> data, QString datatype);
    void createCombinedChart();

    void getTimeDate();


private:
    std::tuple<QString, QString> parseTimeDate(QString t, QString type);
    NetworkHandler* networkhandler_;
    MainWindow* view_;

    std::unordered_map<QString, QString> digitrafficData;
    std::unordered_map<QString,std::vector<double>> fmiData;
    std::tuple<QString, QString> startNendTime;
    QString source_;
    QString datatype_;
    QString location_;

    bool digitrafficReady;
    bool fmiReady;
};
#endif // CONTROLLER_H
