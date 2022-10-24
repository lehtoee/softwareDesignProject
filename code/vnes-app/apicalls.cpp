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

 // Data vector = depending on selected location: x_min, x_max, y_min, y_max (float)
apiCalls::apiCalls(std::string source, float data)
{
 if (source == "FMI")
 {
     std::cout<<source<<std::endl;
 }
 else if (source == "Digitraffic")
 {
     QEventLoop eventLoop;

     QString url = "https://tie.digitraffic.fi/api/v3/data/road-conditions/21/61/22/62";

     QNetworkAccessManager *mgr = new QNetworkAccessManager();

     QNetworkRequest request = QNetworkRequest(QUrl(url));
     QNetworkReply* reply = mgr->get(request);
     eventLoop.exec();
     if (reply->error() == QNetworkReply::NoError) {
         qDebug() << "Jee";


     }
     else {
         qDebug() << "eii";
     }


     // std::cout<<source<<std::endl;





 }
 else if (source == "Both")
 {
     std::cout<<source<<std::endl;
 }
 else {
     std::cout << "error" << std::endl;
 }
}
