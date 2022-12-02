#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler)
    : networkhandler_(networkhandler)
{
<<<<<<< code/vnes-app/controller.cpp
    std::unordered_map<QString, QString> digitrafficData;
    //timeNDate timeDate;
    //getTimeDate();
    std::unordered_map<QString, QString> trafficmessages;
    std::unordered_map<QString, QString> maintenance;
    std::unordered_map<QString, QString> roadconditions;
=======
    //timeNDate timeDate;
    //getTimeDate();
    std::unordered_map<QString, QString> digitrafficData;
>>>>>>> code/vnes-app/controller.cpp
}

Controller::~Controller()
{
    delete networkhandler_;
}

void Controller::pushButtonClicked(QString source, QString datatype,
                                   std::vector<QString> coordinates, QString time )
{
    // Get the start and end time of
<<<<<<< code/vnes-app/controller.cpp
    std::tuple<QString, QString> startNendTime = parseTimeDate("2");
    qDebug() << get<0>(startNendTime) + " - " + get<1>(startNendTime);
    networkhandler_->fetchDataXML("weatherObserved", coordinates, startNendTime);
=======
    std::tuple<QString, QString> startNendTime = parseTimeDate("6");
    qDebug() << get<0>(startNendTime) + " - " + get<1>(startNendTime);
    networkhandler_->fetchDataXML("weatherObserved", "Tampere", startNendTime);
>>>>>>> code/vnes-app/controller.cpp
    //this->coordinates_ = coordinates;

    networkhandler_->fetchDataJson(source, datatype, coordinates, time);
    QJsonObject jsonData = networkhandler_->getJsonData();
    //some async stuff would be needed here
    //parseDigitrafficData(jsonData, datatype);
}

<<<<<<< code/vnes-app/controller.cpp
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
=======
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
>>>>>>> code/vnes-app/controller.cpp
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
<<<<<<< code/vnes-app/controller.cpp
                                             .value("forecastConditionReason").toObject()
                                             .value("precipitationCondition").toString();
        QString winterSlipperiness = roadConditions[forecast].toObject()
                                         .value("forecastConditionReason").toObject()
                                         .value("winterSlipperiness").toString();
=======
                .value("forecastConditionReason").toObject()
                .value("precipitationCondition").toString();
        QString winterSlipperiness = roadConditions[forecast].toObject()
                .value("forecastConditionReason").toObject()
                .value("winterSlipperiness").toString();
>>>>>>> code/vnes-app/controller.cpp
        /*QString roadCondition = roadConditions[forecast].toObject()
                .value("forecastConditionReason").toObject()
                .value("roadCondition").toString();*/
        QString overallRoadCondition = roadConditions[forecast].toObject()
<<<<<<< code/vnes-app/controller.cpp
                                           .value("overallRoadCondition").toString();
        QString weatherSymbol = roadConditions[forecast].toObject()
                                    .value("weatherSymbol").toString();

        digitrafficData.insert({{"precipitationCondition", precipitationCondition},
            {"winterSlipperiness", winterSlipperiness},
            {"overallRoadCondition", overallRoadCondition},
            {"weatherSymbol", weatherSymbol}
        });
=======
                .value("overallRoadCondition").toString();
        QString weatherSymbol = roadConditions[forecast].toObject()
                .value("weatherSymbol").toString();

        digitrafficData.insert({{"precipitationCondition", precipitationCondition},
                               {"winterSlipperiness", winterSlipperiness},
                               {"overallRoadCondition", overallRoadCondition},
                               {"weatherSymbol", weatherSymbol}
                               });
>>>>>>> code/vnes-app/controller.cpp


    }
    else if(datatype == "trafficmessages"){
<<<<<<< code/vnes-app/controller.cpp

        QJsonArray features = jsonData["features"].toArray();
=======
        //this thing counts the traffic messages for the given area
        std::vector<QString> coordinates_({"22","60","28","62"});



        QJsonArray features = jsonData_["features"].toArray();
        QJsonArray geometry;
>>>>>>> code/vnes-app/controller.cpp

        int count = 0;
        for(auto ele : features){
            QString type = ele.toObject().value("geometry")
<<<<<<< code/vnes-app/controller.cpp
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
=======
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
>>>>>>> code/vnes-app/controller.cpp
                }

            }
            else if(type=="MultiLineString"){
                QJsonArray multiCoord = coords[0].toArray()[0].toArray();
<<<<<<< code/vnes-app/controller.cpp
                if(multiCoord[0].toDouble() > coordinates[0].toDouble()
                    && multiCoord[0].toDouble() < coordinates[2].toDouble()
                    && multiCoord[1].toDouble() > coordinates[1].toDouble()
                    && multiCoord[1].toDouble() < coordinates[3].toDouble())
=======
                if(multiCoord[0].toDouble() > coordinates_[0].toDouble()
                        && multiCoord[0].toDouble() < coordinates_[2].toDouble()
                        && multiCoord[1].toDouble() > coordinates_[1].toDouble()
                        && multiCoord[1].toDouble() < coordinates_[3].toDouble())
>>>>>>> code/vnes-app/controller.cpp
                {
                    count++;
                }
            }

        }

        QString stringCount = "count";
<<<<<<< code/vnes-app/controller.cpp

        digitrafficData.insert({stringCount, QString::number(count)});
    }
}

void Controller::parseFMIData(QString datatype)
{

}
/*
void Controller::getTimeDate()
{
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    timeDate.year = localTime->tm_year; //+ 1900;
    timeDate.month = localTime->tm_mon; //+ 1;
    timeDate.day = localTime->tm_mday;
    timeDate.hour = localTime->tm_hour;
    timeDate.minute = localTime->tm_min;
}*/
=======
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
>>>>>>> code/vnes-app/controller.cpp

std::tuple<QString, QString> Controller::parseTimeDate(QString t)
{
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
<<<<<<< code/vnes-app/controller.cpp
=======
    localTime->tm_hour -= 2;
>>>>>>> code/vnes-app/controller.cpp
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
