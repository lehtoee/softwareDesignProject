#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler, MainWindow* view)
    : networkhandler_(networkhandler),
    view_(view)
{
    std::unordered_map<QString, QString> digitrafficData;
    //timeNDate timeDate;
    //getTimeDate();
    std::unordered_map<QString, QString> trafficmessages;
    std::unordered_map<QString, QString> maintenance;
    std::unordered_map<QString, QString> roadconditions;

    connect(view_, &MainWindow::fetchDigiTraffic, this, &Controller::pushButtonClicked);
    connect(view_, &MainWindow::fetchFMI, this, &Controller::pushButtonClicked);

    connect(networkhandler_, &NetworkHandler::jsonReady, this, &Controller::createDigiTrafficChart);
    connect(networkhandler_, &NetworkHandler::xmlReady, this, &Controller::createFMIChart);
}

Controller::~Controller()
{
    delete networkhandler_;
    delete view_;
}

void Controller::pushButtonClicked(QString source, QString datatype,
                                   QString location, QString time )
{
    // Get the start and end time of
    std::tuple<QString, QString> startNendTime = parseTimeDate(time, datatype);
    qDebug() << get<0>(startNendTime) + " - " + get<1>(startNendTime);
    if(source == "FMI"){
        networkhandler_->fetchDataXML(datatype, location, startNendTime);
    }
    else{
        networkhandler_->fetchDataJson(datatype, location, time);

    }

}

void Controller::createDigiTrafficChart(std::unordered_map<QString, QString> data, QString datatype, std::vector<QString> coordinates, QString time)
{
    //std::unordered_map<QString, QString> data = networkhandler_->getJsonData();
    view_->createChart("traffic", datatype, data, {}, datatype, "observed");
    //view_.&MainWindow::createChart("traffic", "maintenance", data, {});
}

void Controller::createFMIChart(std::unordered_map<QString, std::vector<double> > data, QString datatype)
{
    view_->createChart("weather", datatype, {}, data, "", "");
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



std::tuple<QString, QString> Controller::parseTimeDate(QString t, QString type)
{
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);

    localTime->tm_hour -= 2;

    if (type == "observed"){

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

        else if (t == "4"){

            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            if (localTime->tm_hour < 4){
                int diff = localTime->tm_hour - 4;
                localTime->tm_hour = 24 - diff;
                localTime->tm_mday -= 1;
            }
            else{
                localTime->tm_hour -= 4;
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
            if (localTime->tm_hour > 24 - 2){
                int diff = localTime->tm_hour + 2 - 24;
                localTime->tm_hour = diff;
                localTime->tm_mday += 1;
            }
            else{
                localTime->tm_hour += 2;
            }
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{endtime, starttime};
        }

        else if (t == "4"){

            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            if (localTime->tm_hour > 24 - 4){
                int diff = localTime->tm_hour + 4 - 24;
                localTime->tm_hour = diff;
                localTime->tm_mday += 1;
            }
            else{
                localTime->tm_hour += 4;
            }
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{endtime, starttime};
        }


        else if (t == "6"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            if (localTime->tm_hour > 24 - 6){
                int diff = localTime->tm_hour + 6 - 24;
                localTime->tm_hour = diff;
                localTime->tm_mday += 1;
            }
            else{
                localTime->tm_hour += 6;
            }
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{endtime, starttime};

        }
        else if (t == "12") {
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            if (localTime->tm_hour > 24 - 12){
                int diff = localTime->tm_hour + 12 - 24;
                localTime->tm_hour = diff;
                localTime->tm_mday += 1;
            }
            else{
                localTime->tm_hour += 12;
            }
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{endtime, starttime};

        }
        else if (t=="24"){
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            localTime->tm_mday += 1;
            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString starttime = format;

            return std::tuple<QString, QString>{endtime, starttime};
        }
    }
}
