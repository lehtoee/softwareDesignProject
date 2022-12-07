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
    void createDigiTrafficChart(std::unordered_map<QString, QString> data, QString datatype, std::vector<QString> coordinates, QString time);
    void createFMIChart(std::unordered_map<QString, std::vector<double>> data, QString datatype);
    void createCombinedChart(std::unordered_map<QString, std::vector<double>> FMIdata,
                             std::unordered_map<QString, std::vector<double>> digiTrafficData, QString datatype);
    void parseFMIData(QString datatype);

    void getTimeDate();


private:
    std::tuple<QString, QString> parseTimeDate(QString t, QString type);
    NetworkHandler* networkhandler_;
    MainWindow* view_;
    struct timeNDate{
        int hour;
        int minute;
        int year;
        int month;
        int day;
    } timeDate;
    std::unordered_map<QString, QString> digitrafficData;
    QString source_;

    //testimapit
    std::unordered_map<QString, QString> trafficmessages;
    std::unordered_map<QString, QString> maintenance;
    std::unordered_map<QString, QString> roadconditions;
    // timeNDate timeDate;


};
#endif // CONTROLLER_H
