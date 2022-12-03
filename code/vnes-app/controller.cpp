#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler)
    : networkhandler_(networkhandler)
{
    std::unordered_map<QString, QString> digitrafficData;
    //timeNDate timeDate;
    //getTimeDate();
    std::unordered_map<QString, QString> trafficmessages;
    std::unordered_map<QString, QString> maintenance;
    std::unordered_map<QString, QString> roadconditions;
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

    networkhandler_->fetchDataJson(source, datatype, coordinates, time);
    QJsonObject jsonData = networkhandler_->getJsonData();
    //some async stuff would be needed here
    //parseDigitrafficData(jsonData, datatype);
}


std::unordered_map<QString, QString> Controller::getData(QString type)
{
    if(type=="trafficmessages"){
        trafficmessages = {{"count", "5"}};
        return trafficmessages;
    }
    else if(type=="roadconditions"){
        roadconditions = {{{"precipitationCondition", "NO_RAIN_DRY_WEATHER"},
            {"winterSlipperiness", ""},
            {"overallRoadCondition", "NORMAL_CONDITION"},
            {"weatherSymbol", "n300"}
        }};
        return roadconditions;
    }
    else if(type=="maintenance"){
        maintenance = {{"task1", "LINE_SANDING"},
                       {"task2", "ROAD_STATE_CHECKING"},
                       {"task3", "ROAD_STATE_CHECKING"},
                       {"task4", "BRUSHING"},
                       {"task5", "CLEANSING_OF_BRIDGES"}};
        return maintenance;
    }
    return digitrafficData;
}

void Controller::parseDigitrafficData(QJsonObject jsonData, QString datatype)
{
    std::vector<QString> coordinates({"22","60","28","62"});

    digitrafficData.clear();
    int timeTemp;
    if(datatype == "maintenance"){
        QJsonArray maintenanceFeatures = jsonData["features"].toArray();
        int counter = 1;
        for(auto ele : maintenanceFeatures){
            QString task = ele.toObject().value("properties")
                               .toObject().value("tasks")[0].toString();
            digitrafficData.insert({"task" + QString::number(counter), task});
            counter++;
        }
    }
    else if(datatype == "roadconditions"){
        QJsonArray weatherData = jsonData["weatherData"].toArray();

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
        QString roadCondition = roadConditions[forecast].toObject()
             .value("forecastConditionReason").toObject()
             .value("roadCondition").toString();
        QString overallRoadCondition = roadConditions[forecast].toObject()
             .value("overallRoadCondition").toString();
        QString roadTemperature = roadConditions[forecast].toObject()
             .value("roadTemperature").toString();
        QString temperature = roadConditions[forecast].toObject()
             .value("temperature").toString();
        QString windSpeed = roadConditions[forecast].toObject()
             .value("windSpeed").toString();
        QString windDirection = roadConditions[forecast].toObject()
             .value("windDirection").toString();
        QString weatherSymbol = roadConditions[forecast].toObject()
             .value("weatherSymbol").toString();

        digitrafficData.insert({{"precipitationCondition", precipitationCondition},
            {"winterSlipperiness", winterSlipperiness},
            {"overallRoadCondition", overallRoadCondition},
            {"weatherSymbol", weatherSymbol},
            {"roadCondition", roadCondition},
            {"roadTemperature", roadTemperature},
            {"temperature", temperature},
            {"windSpeed", windSpeed},
            {"windDirection", windDirection}
        });


    }
    else if(datatype == "trafficmessages"){

        QJsonArray features = jsonData["features"].toArray();

        int count = 0;
        for(auto ele : features){
            QString type = ele.toObject().value("geometry")
                               .toObject().value("type").toString();
            QJsonArray coords = ele.toObject().value("geometry")
                                    .toObject().value("coordinates").toArray();

            if(type == "Point"){
                if(coords[0].toDouble() > coordinates[0].toDouble()
                    && coords[0].toDouble() < coordinates[2].toDouble()
                    && coords[1].toDouble() > coordinates[1].toDouble()
                    && coords[1].toDouble() < coordinates[3].toDouble())
                {
                    count++;
                }

            }
            else if(type=="MultiLineString"){
                QJsonArray multiCoord = coords[0].toArray()[0].toArray();
                if(multiCoord[0].toDouble() > coordinates[0].toDouble()
                    && multiCoord[0].toDouble() < coordinates[2].toDouble()
                    && multiCoord[1].toDouble() > coordinates[1].toDouble()
                    && multiCoord[1].toDouble() < coordinates[3].toDouble())
                {
                    count++;
                }
            }

        }

        QString stringCount = "count";

        digitrafficData.insert({stringCount, QString::number(count)});
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
