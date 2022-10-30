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
#include <QIODevice>

apiCalls::apiCalls(QObject *parent) : QObject(parent)
{
    mgr = new QNetworkAccessManager(this);
    connect(mgr, &QNetworkAccessManager::finished, this, &apiCalls::apiData);
    connect(mgr, &QNetworkAccessManager::finished, mgr, &QNetworkReply::deleteLater);
    //connect(mgr, &QNetworkAccessManager::sslErrors, this, &apiCalls::apiError);
    //QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiData(QNetworkReply*)));
    //QObject::connect(mgr, SIGNAL(sslErrors(QNetworkReply*)), this, SLOT(apiError()));

}

apiCalls::~apiCalls()
{

}

void apiCalls::pullData(std::string source)
{
    //mgr = new QNetworkAccessManager(this);
    //QNetworkReply* reply;
    //QObject::connect(mgr, &QNetworkAccessManager::finished, this, &apiCalls::apiData);

    //QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiData(QNetworkReply*)));
    //QObject::connect(reply, &QNetworkReply::finished, this, apiData(reply))
   // QObject::connect(mgr, SIGNAL(errorOccurred(QNetworkReply*)), this, SLOT(apiError(QNetworkReply::NetworkError*)));
    if (source == "FMI")
    {
        QString url = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&bbox=23,61,24,62&timestep=30&parameters=t2m,ws_10min,n_man";
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        mgr->get(request);
        //QNetworkReply *reply = mgr->get(QNetworkRequest(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&bbox=23,61,24,62&timestep=30&parameters=t2m,ws_10min,n_man")));
        //connect(reply, &QNetworkReply::errorOccurred, this, &apiCalls::apiError);
        // QObject::connect(reply, SIGNAL(errorOccurred(QNetworkReply::NetworkError)), this, SLOT(apiError(QNetworkReply::NetworkError*)));
        std::cout<<source<<std::endl;
    }
    else if (source == "Digitraffic")
    {
        QString url = "https://tie.digitraffic.fi/api/v3/data/road-conditions/21/61/22/62";
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        qDebug() << "tähä";
        mgr->get(request);
        //QNetworkReply *reply = mgr->get(request);
        //connect(reply, &QNetworkReply::finished, this, &apiCalls::apiData);
        std::cout<<"aivanjoo"<<std::endl;
    }
    else if (source == "Both")
    {
        std::cout<<source<<std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }

}

void apiCalls::apiData(QNetworkReply* reply)
{
    qDebug() << "Tänne";
    if(reply->error()){
            qDebug() << reply->errorString();
}
    else{
        qDebug() << "No error";
    }
    /*QString answer = reply->readAll();
    qDebug()<<answer;
    QByteArray buffer = reply->readAll();
    qDebug() << buffer;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();
    QJsonArray features = jsonReply["weatherData"].toArray();
    qDebug() << features;*/
    reply->deleteLater();
}
/*
void apiCalls::apiError(QNetworkReply* reply, QList<QSslError> &errors)
{
    qDebug()<<"Voi ei";
}
*/
