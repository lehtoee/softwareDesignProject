#include "apicalls.hh"
#include <iostream>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <vector>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>


apiCalls::apiCalls(QObject *parent) : QObject(parent)
{

}

apiCalls::~apiCalls()
{

}

void apiCalls::pullData(std::string source)
{
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiData(QNetworkReply*)));
    if (source == "FMI")
    {
        std::cout<<source<<std::endl;
    }
    else if (source == "Digitraffic")
    {
        QString url = "https://tie.digitraffic.fi/api/v3/data/road-conditions/21/61/22/62";
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        mgr->get(request);
        std::cout<<"aivanjoo"<<std::endl;
    }
    else if (source == "Both")
    {
        std::cout<<source<<std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
    std::cin.ignore();
    return;

}

void apiCalls::apiData(QNetworkReply* reply)
{
    std::cout<<"aivan"<<std::endl;
    QString answer = reply->readAll();
    qDebug()<<answer;
    QByteArray buffer = reply->readAll();
    qDebug() << buffer;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();
    QJsonArray features = jsonReply["weatherData"].toArray();
    qDebug() << features;
}
