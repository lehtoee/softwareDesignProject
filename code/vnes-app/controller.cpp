#include "controller.h"
#include <ctime>

Controller::Controller(NetworkHandler* networkhandler)
    : networkhandler_(networkhandler)
{
    timeNDate timeDate;
    getTimeDate();
}

Controller::~Controller()
{
    delete networkhandler_;
}

void Controller::pushButtonClicked(std::string source, std::string datatype,
                                   std::vector<QString> coordinates, std::string time )
{
    qDebug()<<timeDate.day;
    networkhandler_->fetchDataJson(source, datatype, coordinates, time);
    QJsonObject jsonData = networkhandler_->getJsonData();
    //some async stuff would be needed here
    //parseDigitrafficData(jsonData, datatype);
}

void Controller::parseDigitrafficData(QJsonObject jsonData, std::string datatype)
{
    if(datatype == "maintenance"){

    }
    else if(datatype == "roadconditions"){
        /*QJsonArray weatherData = jsonData_["weatherData"].toArray();

        QJsonArray roadConditions = weatherData[0].toObject()
                .value("roadConditions").toArray();
        int forecast = 1;
        if(time == 2){
            forecast = 1;
        }
        else if(time == 4){
            forecast = 2;
        }
        else if(time == 6){
            forecast = 3;
        }
        else if(time == 12){
            forecast = 4;
        }
        if(type == precipitation){
            QString precipitationCondition = roadConditions[forecast].toObject()
                    .value("forecastConditionReason").toObject()
                    .value("precipitationCondition");
        }
        if(type == slipperiness){
            QString winterSlipperiness = roadConditions[forecast].toObject()
                    .value("forecastConditionReason").toObject()
                    .value("precipitationCondition");
        }
        if(type == condition){
            QString roadCondition = roadConditions[forecast].toObject()
                    .value("forecastConditionReason").toObject()
                    .value("roadCondition");
        }*/
    }
    else if(datatype == "trafficmessages"){
        //this thing counts the traffic messages for the given area
        /*
        QJsonArray features = jsonData_["features"].toArray();
        QJsonArray geometry;

        int count = 0;
        for(auto ele : features){
            QString type = ele.toObject().value("geometry")
                    .toObject().value("type").toString();
            QJsonArray coords = ele.toObject().value("geometry")
                    .toObject().value("coordinates").toArray();
            qDebug() << type;
            qDebug() << ele.toObject().value("geometry").toObject().value("coordinates").toArray();

            if(type == "Point"){
                if(coords[0].toDouble() > coordinates[0]
                        && coords[0].toDouble() < coordinates[2]
                        && coords[1].toDouble() > coordinates[1]
                        && coords[1].toDouble() < coordinates[3])
                {
                        count++;
                }

            }
            else if(type=="MultiLineString"){
                QJsonArray multiCoord = coords[0].toArray()[0].toArray();
                if(multiCoord[0].toDouble() > coordinates[0]
                        && multiCoord[0].toDouble() < coordinates[2]
                        && multiCoord[1].toDouble() > coordinates[1]
                        && multiCoord[1].toDouble() < coordinates[3])
                {
                    count++;
                }
            }

        }
        qDebug() << "dfsmiaod";
        qDebug() << count;
        */
    }
}

void Controller::parseFMIData(std::string datatype)
{

}

void Controller::getTimeDate()
{

    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);
    timeDate.year = localTime->tm_year + 1900;
    timeDate.month = localTime->tm_mon + 1;
    timeDate.day = localTime->tm_mday;
    timeDate.hour = localTime->tm_hour;
    timeDate.minute = localTime->tm_min;
}
