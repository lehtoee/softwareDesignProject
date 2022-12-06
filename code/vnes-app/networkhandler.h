#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <map>
#include <QFile>
#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <utils.h>
#include <QXmlStreamReader>


class NetworkHandler : public QObject
{
    Q_OBJECT

public:
    NetworkHandler(QObject* parent = nullptr);

    void fetchDataJson(QString datatype, QString location, QString time);
    std::unordered_map<QString, QString> getJsonData();
    void fetchDataXML(QString datatype, QString location, std::tuple<QString, QString> time);

signals:
    void jsonReady(std::unordered_map<QString, QString> data, QString datatype, std::vector<QString> coordinates, QString time);

private slots:
    void jsonFetchFinished(QNetworkReply* reply);
    void XMLFetchFinished(QNetworkReply* reply);

private:
    std::unordered_map<QString, QString> jsonData_;
    utils *utilities;
    QString datatype_;
    std::vector<QString> coordinates_;
    QString time_;

};

#endif // NETWORKHANDLER_H
