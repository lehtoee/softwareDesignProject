#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <map>
#include <QFile>
#include <iostream>


class NetworkHandler : public QObject
{
    Q_OBJECT

public:
    NetworkHandler(QObject* parent = nullptr);

    void fetchDataJson(std::string source, std::string datatype,
                       std::vector<QString> coordinates, std::string time);
    QJsonObject getJsonData();
    void fetchDataXML(QString datatype, std::vector<QString> coordinates, std::tuple<QString, QString> time);

private slots:
    void jsonFetchFinished(QNetworkReply* reply);

private:
    //QString myurl = "https://tie.digitraffic.fi/api/maintenance/v1/tracking/routes?endFrom=2022-01-19T09%3A00%3A00Z&endBefore=2022-01-19T14%3A00%3A00Z&xMin=21&yMin=61&xMax=22&yMax=62&taskId=&domain=state-roads";
    //QString myurl = "https://tie.digitraffic.fi/api/v3/data/road-conditions/21/61/22/62";
    QJsonObject jsonData_;

};

#endif // NETWORKHANDLER_H
