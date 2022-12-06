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
                                   QString location, QString time )
{
    // Get the start and end time of
    std::tuple<QString, QString> startNendTime = parseTimeDate("6");
    qDebug() << get<0>(startNendTime) + " - " + get<1>(startNendTime);
    networkhandler_->fetchDataXML("weatherObserved", "Tampere", startNendTime);

    networkhandler_->fetchDataJson(datatype, location, time);
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
        roadconditions = {{"precipitationCondition", "NO_RAIN_DRY_WEATHER"},
            {"winterSlipperiness", ""},
            {"overallRoadCondition", "NORMAL_CONDITION"},
            {"weatherSymbol", "n300"},
          {"roadCondition", "DRY"},
          {"roadTemperature", "+17"},
          {"temperature", "+13"},
          {"windSpeed", "2.0"},
          {"windDirection", "45"}
        };
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



std::tuple<QString, QString> Controller::parseTimeDate(QString t)
{
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);

    localTime->tm_hour -= 2;

    if (type == "observation"){
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
        else if (t=="24"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            localTime->tm_mday -= 1;
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{starttime, endtime};
        }
        else if(t=="1m"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            localTime->tm_mon -= 1;
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;
        }
    }
    else {
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
        else if (t=="24"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            localTime->tm_mday -= 1;
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{starttime, endtime};
        }
        else if(t=="1m"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            localTime->tm_mon -= 1;
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;
        }
    }
}
