#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "networkhandler.h"
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
    Controller(NetworkHandler* networkhandler);
    ~Controller();

    void pushButtonClicked(QString source, QString datatype,
                           std::vector<QString> coordinates, QString time);
    void parseDigitrafficData(QJsonObject jsonData, QString datatype);
    void parseFMIData(QString datatype);
    void getTimeDate();

private:
    std::tuple<QString, QString> parseTimeDate(QString time);
    NetworkHandler* networkhandler_;
    struct timeNDate{
        int hour;
        int minute;
        int year;
        int month;
        int day;
    } timeDate;
   std::unordered_map<QString, QString> digitrafficData;
   //std::vector<QString> coordinates_;
   // timeNDate timeDate;

};
#endif // CONTROLLER_H
