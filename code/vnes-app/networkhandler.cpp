#include "networkhandler.h"
#include <QJsonArray>
#include <sstream>

NetworkHandler::NetworkHandler(QObject *parent):
    QObject{parent}
{
    utils *utilities = new utils;
}

void NetworkHandler::fetchDataJson(QString source, QString datatype,
                                   std::vector<QString> coordinates, QString time)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHandler::jsonFetchFinished);

    QString myurl = "https://tie.digitraffic.fi/api/";
    if(datatype == "maintenance"){
        QString qstrtime = time;
        myurl = myurl + "maintenance/v1/tracking/routes?endFrom="
                + "2022-01-19T09%3A00%3A00Z" + "&endBefore=" + "2022-01-19T10%3A00%3A00Z" + "&xMin="
                + coordinates[0] + "&yMin=" + coordinates[1] + "&xMax="
                + coordinates[2] + "&yMax=" + coordinates[3]
                + "&taskId=&domain=state-roads";

    }
    else if(datatype == "roadconditions"){

        myurl = myurl + "v3/data/road-conditions/" + coordinates[0] + "/"
                + coordinates[1] + "/" + coordinates[2] + "/"
                + coordinates[3];
    }
    else if(datatype == "trafficmessages"){
        myurl= myurl + "traffic-message/v1/messages?inactiveHours="
                        "&includeAreaGeometry=false&situationType=";
    }
    const QUrl url = QUrl(myurl);
    QNetworkRequest request(url);
    manager->get(request);
}

QJsonObject NetworkHandler::getJsonData()
{
    return jsonData_;
}


void NetworkHandler::jsonFetchFinished(QNetworkReply *reply)
{
    if(reply->error()){
        qDebug() << "error";
        qDebug() << reply->errorString();
        return;
    }
    qDebug() << "fetch ok";


    //convert to Json object
    QByteArray input = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(input);
    QJsonObject obj = document.object();
    jsonData_ = obj;
    // Tähän joku emit jonka controller sitte pick uppaa että tän jsonData_ muuttujan saa tallennettuu johki
    qDebug() << jsonData_;
    reply->deleteLater();
}



void NetworkHandler::fetchDataXML(QString datatype, QString location, std::tuple<QString, QString> time)
{
    QNetworkAccessManager *xmlmanager = new QNetworkAccessManager(this);
    connect(xmlmanager, &QNetworkAccessManager::finished, this, &NetworkHandler::XMLFetchFinished);

    QString GeoID = utilities->getGeoID(location);
    QString baseURL = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi";
    QString URLstring;

    if(datatype == "weatherObserved"){
        URLstring = baseURL+"::observations::weather::hourly::simple&geoid="+GeoID+
                "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=t2m,ws_10min";
        qDebug() << URLstring;
    }
    else if(datatype == "weatherForecast") {
        URLstring = baseURL+"::forecast::harmonie::surface::point::simple&geoid="+GeoID+
                "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=temperature,windspeedms";
        qDebug()<<URLstring;
    }
    else {
        URLstring = "";
    }
    const QUrl url = QUrl(URLstring);
    QNetworkRequest request(url);
    xmlmanager->get(request);
}

void NetworkHandler::XMLFetchFinished(QNetworkReply *reply)
{
    if(reply->error()){
        qDebug() << "error";
        qDebug() << reply->errorString();
        return;
    }
    qDebug() << "XML Fetch ok";
    QByteArray byteArrayContent = reply->readAll();
    QString content = QString(byteArrayContent);
    std::unordered_map<QString, std::vector<double>> FMIdata = utilities->parseXML(content);
    qDebug() << "tänne";
}


