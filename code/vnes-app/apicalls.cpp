#include "apicalls.hh"
#include <iostream>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <vector>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QEventLoop>


apiCalls::apiCalls()
{

}

apiCalls::~apiCalls()
{

}

void apiCalls::pullData(std::string source)
{
    QEventLoop loop;
    QNetworkAccessManager *mgr = new QNetworkAccessManager();
    QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(apiData(QNetworkReply*)));
    QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    if (source == "FMI")
    {
        std::cout<<source<<std::endl;
    }
    else if (source == "Digitraffic")
    {
        QString url = "https://tie.digitraffic.fi/api/v3/data/road-conditions/21/61/22/62";
        QNetworkRequest request = QNetworkRequest(QUrl(url));
        mgr->get(request);
        loop.exec();
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
    qDebug()<<reply->readAll();;
}
