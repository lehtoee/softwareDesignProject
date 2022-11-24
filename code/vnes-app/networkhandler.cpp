#include "networkhandler.h"
#include <QJsonArray>
#include <sstream>

NetworkHandler::NetworkHandler(QObject *parent):
 QObject{parent}
{
}

void NetworkHandler::fetchDataJson(std::string source, std::string datatype,
                                   std::vector<QString> coordinates, std::string time)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHandler::jsonFetchFinished);

    if(source == "FMI"){
        QString baseURL = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi";
        if(datatype == "weather"){
            QString URL = baseURL+"::observations::weather::hourly::simple&bbox=" + coordinates[0]+","+coordinates[2]+","+coordinates[1]+","+coordinates[3]+"&starttime=";

        }
        else if(datatype == "rainfall") {

        }
    }
    else if(source == "Digitraffic"){
        QString myurl = "https://tie.digitraffic.fi/api/";
        if(datatype == "maintenance"){
            QString qstrtime = QString::fromStdString(time);
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
    else if(source == "both"){

    }
    else{
        std::cout << "error" << std::endl;
    }
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

