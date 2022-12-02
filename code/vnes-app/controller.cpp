#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler)
    : networkhandler_(networkhandler)
{
    //timeNDate timeDate;
    //getTimeDate();
    std::unordered_map<QString, QString> digitrafficData;
}

Controller::~Controller()
{
    delete networkhandler_;
}

void Controller::pushButtonClicked(QString source, QString datatype,
                                   std::vector<QString> coordinates, QString time )
{
    // Get the start and end time of
    std::tuple<QString, QString> startNendTime = parseTimeDate("6");
    qDebug() << get<0>(startNendTime) + " - " + get<1>(startNendTime);
    networkhandler_->fetchDataXML("weatherObserved", "Tampere", startNendTime);
    //this->coordinates_ = coordinates;

    networkhandler_->fetchDataJson(source, datatype, coordinates, time);
    QJsonObject jsonData = networkhandler_->getJsonData();
    //some async stuff would be needed here
    //parseDigitrafficData(jsonData, datatype);
}

void Controller::parseDigitrafficData(QJsonObject jsonData, QString datatype)
{

    QJsonObject jsonData_ = networkhandler_->getJsonData();
    int timeTemp;
    if(datatype == "maintenance"){
         QJsonArray maintenanceFeatures = jsonData_["features"].toArray();
         int counter = 1;
         for(auto ele : maintenanceFeatures){
             QString task = ele.toObject().value("properties")
                     .toObject().value("tasks")[0].toString();
             digitrafficData.insert({"task" + QString::number(counter), task});
             counter++;
         }
    }
    else if(datatype == "roadconditions"){
        QJsonArray weatherData = jsonData_["weatherData"].toArray();

        QJsonArray roadConditions = weatherData[0].toObject()
                .value("roadConditions").toArray();
        int forecast = 1;
        if(timeTemp == 2){
            forecast = 1;
        }
        else if(timeTemp == 4){
            forecast = 2;
        }
        else if(timeTemp == 6){
            forecast = 3;
        }
        else if(timeTemp == 12){
            forecast = 4;
        }

        QString precipitationCondition = roadConditions[forecast].toObject()
                .value("forecastConditionReason").toObject()
                .value("precipitationCondition").toString();
        QString winterSlipperiness = roadConditions[forecast].toObject()
                .value("forecastConditionReason").toObject()
                .value("winterSlipperiness").toString();
        /*QString roadCondition = roadConditions[forecast].toObject()
                .value("forecastConditionReason").toObject()
                .value("roadCondition").toString();*/
        QString overallRoadCondition = roadConditions[forecast].toObject()
                .value("overallRoadCondition").toString();
        QString weatherSymbol = roadConditions[forecast].toObject()
                .value("weatherSymbol").toString();

        digitrafficData.insert({{"precipitationCondition", precipitationCondition},
                               {"winterSlipperiness", winterSlipperiness},
                               {"overallRoadCondition", overallRoadCondition},
                               {"weatherSymbol", weatherSymbol}
                               });


    }
    else if(datatype == "trafficmessages"){
        //this thing counts the traffic messages for the given area
        std::vector<QString> coordinates_({"22","60","28","62"});



        QJsonArray features = jsonData_["features"].toArray();
        QJsonArray geometry;

        int count = 0;
        for(auto ele : features){
            QString type = ele.toObject().value("geometry")
                    .toObject().value("type").toString();
            QJsonArray coords = ele.toObject().value("geometry")
                    .toObject().value("coordinates").toArray();

            if(type == "Point"){
                if(coords[0].toDouble() > coordinates_[0].toDouble()
                        && coords[0].toDouble() < coordinates_[2].toDouble()
                        && coords[1].toDouble() > coordinates_[1].toDouble()
                        && coords[1].toDouble() < coordinates_[3].toDouble())
                {
                        count++;
                }

            }
            else if(type=="MultiLineString"){
                QJsonArray multiCoord = coords[0].toArray()[0].toArray();
                if(multiCoord[0].toDouble() > coordinates_[0].toDouble()
                        && multiCoord[0].toDouble() < coordinates_[2].toDouble()
                        && multiCoord[1].toDouble() > coordinates_[1].toDouble()
                        && multiCoord[1].toDouble() < coordinates_[3].toDouble())
                {
                    count++;
                }
            }

        }

        QString stringCount = "count";
        auto it = digitrafficData.find(stringCount);

        if(it != digitrafficData.end()){
            qDebug() << "joo";
            it->second = QString::number(5);
        }
        else{
            qDebug() << "noniin";
            digitrafficData.insert({stringCount, QString::number(count)});
        }

        auto iter = digitrafficData.find("count");


        //digitrafficData.insert({"count", QString::number(5)});

        for(auto ele : digitrafficData){
            qDebug() << ele.second;
        }
    }
}

std::tuple<QString, QString> Controller::parseTimeDate(QString t)
{
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    localTime->tm_hour -= 2;
    if (t == "2"){

        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString endtime = format;
        if (localTime->tm_hour < 2){
            int diff = localTime->tm_hour - 2;
            localTime->tm_hour = 24 - diff;
            localTime->tm_mday -= 1;
        }
        else{
            localTime->tm_hour -= 2;
        }
        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString starttime = format;

        return std::tuple<QString, QString>{starttime, endtime};
    }
    else if (t == "6"){
        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString endtime = format;
        if (localTime->tm_hour < 6){
            int diff = localTime->tm_hour - 6;
            localTime->tm_hour = 24 - diff;
            localTime->tm_mday -= 1;
        }
        else{
            localTime->tm_hour -= 6;
        }
        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString starttime = format;

        return std::tuple<QString, QString>{starttime, endtime};

    }
    else if (t == "12") {
        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString endtime = format;
        if (localTime->tm_hour < 12){
            int diff = localTime->tm_hour - 12;
            localTime->tm_hour = 24 - diff;
            localTime->tm_mday -= 1;
        }
        else{
            localTime->tm_hour -= 12;
        }
        strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
        QString starttime = format;

        return std::tuple<QString, QString>{starttime, endtime};

    }
    else {

    }
}
