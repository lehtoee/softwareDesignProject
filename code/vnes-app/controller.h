#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "networkhandler.h"
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <map>
#include <QFile>
#include <iostream>
#include <QJsonArray>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(NetworkHandler* networkhandler);
    ~Controller();

    void pushButtonClicked(std::string source, std::string datatype,
                           std::vector<QString> coordinates, std::string time);
    void parseDigitrafficData(QJsonObject jsonData, std::string datatype);
    void parseFMIData(std::string datatype);

private:

    NetworkHandler* networkhandler_;

};
#endif // CONTROLLER_H
