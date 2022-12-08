#include "networkhandler.h"
#include <QJsonArray>
#include <sstream>

NetworkHandler::NetworkHandler(QObject *parent):
    QObject{parent}
{
    utils *utilities = new utils;
}

/**
 * @brief NetworkHandler::fetchDataJson
     Function for fetching the data from the Digitraffic API
 * @param datatype
     What data is fetched from the API
 * @param location
     From which city the data is wanted
 * @param time
     From which time the data is wanted
 * @param startEndTime
     From which time the data is wanted converted into time interval
 */
void NetworkHandler::fetchDataJson(QString datatype, QString location, QString time, std::tuple<QString, QString> startEndTime)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkHandler::jsonFetchFinished);

    datatype_ = datatype;
    //converting the selected city into coordinates
    coordinates_ = utilities->getCoordinates(location);
    time_ = time;

    //forming the url for the network request
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

/**
 * @brief NetworkHandler::jsonFetchFinished
     Function for converting the data into QJsonObject, sending it to be parsed
     and finally emiting the data back to the controller
 * @param reply
     The reply from the network request
 */
void NetworkHandler::jsonFetchFinished(QNetworkReply *reply)
{
    //convert to Json object
    QByteArray input = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(input);
    QJsonObject jsonObj = document.object();
    //send it to the parse function in utilities
    jsonData_ = utilities->parseJson(jsonObj, datatype_, coordinates_, time_);

    //emiting signal that the fetch is ready and the data has been parsed
    emit jsonReady(jsonData_, datatype_, coordinates_, time_);

}

/**
 * @brief NetworkHandler::fetchDataXML
 * Function for fetching XML data flie from FMI api
 * @param datatype what data is wanted
 * @param location the city selected by user
 * @param time pair of times formatted for API URL
 */

void NetworkHandler::fetchDataXML(QString datatype, QString location, std::tuple<QString, QString> time)
{
    QNetworkAccessManager *xmlmanager = new QNetworkAccessManager(this);
    connect(xmlmanager, &QNetworkAccessManager::finished, this, &NetworkHandler::XMLFetchFinished);

    // Get the GeoID of the selected location to use in api calls
    QString GeoID = utilities->getGeoID(location);

    // Create the URL based on the requested datatype
    QString baseURL = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi";
    QString URLstring;
    datatype_ = datatype;

    // Observed weather data from the location
    if(datatype == "observed"){
        URLstring = baseURL+"::observations::weather::hourly::simple&geoid="+GeoID+
                    "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=t2m,ws_10min";
    }
    // Forecast of weather based on request from user
    else if(datatype == "forecast") {
        URLstring = baseURL+"::forecast::harmonie::surface::point::simple&geoid="+GeoID+
                    "&starttime="+std::get<0>(time)+"&endtime="+std::get<1>(time)+"&timestep=30&parameters=temperature,windspeedms";
    }
    // Average, max and min temperature from the selected city over a month
    else if(datatype == "lastMonth") {
        URLstring = baseURL+"::observations::weather::daily::simple&geoid="+GeoID+"&parameters=tday,tmax,tmin";
    }
    // Should never get here
    else{
        return;
    }
    // Create a QUrl from the parsed url, create a request and send it using the xmlmanager
    const QUrl url = QUrl(URLstring);
    QNetworkRequest request(url);
    xmlmanager->get(request);
}


/**
 * @brief NetworkHandler::XMLFetchFinished
 * Slot for when reply is finished from FMI api
 * @param reply
 * Reply from api
 * Emits a signal for controller to continue sending the data to frontend
 */
void NetworkHandler::XMLFetchFinished(QNetworkReply *reply)
{
    // Checks if reply is an error and prints out the error to console
    if(reply->error()){
        qDebug() << "error";
        qDebug() << reply->errorString();
        return;
    }
    // Reads the reply from the api and converts it to QString
    QByteArray byteArrayContent = reply->readAll();
    QString content = QString(byteArrayContent);

    // Call the parse function for XML data
    std::unordered_map<QString, std::vector<double>> FMIdata = utilities->parseXML(content);
    emit xmlReady(FMIdata, datatype_);
}
