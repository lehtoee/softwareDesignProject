#include "networkhandler.h"
#include <QJsonArray>
#include <sstream>

NetworkHandler::NetworkHandler(QObject *parent):
    QObject{parent}
{
    utils *utilities = new utils;
}

void NetworkHandler::fetchDataJson(QString datatype, QString location, QString time, std::tuple<QString, QString> startEndTime)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHandler::jsonFetchFinished);

    datatype_ = datatype;
    coordinates_ = utilities->getCoordinates(location);
    time_ = time;

    QString myurl = "https://tie.digitraffic.fi/api/";
    if(datatype == "maintenance"){
        myurl = myurl + "maintenance/v1/tracking/routes?endFrom="
                + get<0>(startEndTime) + "&endBefore=" + get<1>(startEndTime) + "&xMin="
                + coordinates_[0] + "&yMin=" + coordinates_[1] + "&xMax="
                + coordinates_[2] + "&yMax=" + coordinates_[3]
                + "&taskId=&domain=state-roads";

    }
    else if(datatype == "roadconditions"){

        myurl = myurl + "v3/data/road-conditions/" + coordinates_[0] + "/"
                + coordinates_[1] + "/" + coordinates_[2] + "/"
                + coordinates_[3];
    }
    else if(datatype == "trafficmessages"){
        myurl= myurl + "traffic-message/v1/messages?inactiveHours="
                        "&includeAreaGeometry=false&situationType=";
    }
    const QUrl url = QUrl(myurl);
    QNetworkRequest request(url);
    manager->get(request);
}

std::unordered_map<QString, QString> NetworkHandler::getJsonData()
{
    return jsonData_;
}


void NetworkHandler::jsonFetchFinished(QNetworkReply *reply)
{
    //convert to Json object
    QByteArray input = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(input);
    QJsonObject jsonObj = document.object();
    jsonData_ = utilities->parseJson(jsonObj, datatype_, coordinates_, time_);

    emit jsonReady(jsonData_, datatype_, coordinates_, time_);

}



void NetworkHandler::fetchDataXML(QString datatype, QString location, std::tuple<QString, QString> time)
{
    QNetworkAccessManager *xmlmanager = new QNetworkAccessManager(this);
    connect(xmlmanager, &QNetworkAccessManager::finished, this, &NetworkHandler::XMLFetchFinished);

    QString GeoID = utilities->getGeoID(location);
    QString baseURL = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi";
    QString URLstring;
    datatype_ = datatype;

    if(datatype == "observed"){
        URLstring = baseURL+"::observations::weather::hourly::simple&geoid="+GeoID+
                    "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=t2m,ws_10min";
        qDebug() << URLstring;
    }
    else if(datatype == "forecast") {
        URLstring = baseURL+"::forecast::harmonie::surface::point::simple&geoid="+GeoID+
                    "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=temperature,windspeedms";
        qDebug()<<URLstring;
    }
    else if(datatype == "lastMonth") {
        URLstring = baseURL+"::observations::weather::daily::simple&geoid="+GeoID+"&parameters=tday,tmax,tmin";
        qDebug() << URLstring;
    }
    else{
        return;
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
    emit xmlReady(FMIdata, datatype_);
}
