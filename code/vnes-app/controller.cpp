#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler, MainWindow* view)
    : networkhandler_(networkhandler),
    view_(view)
{
    std::unordered_map<QString, QString> digitrafficData;
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
    source_ = source;
    if(source == "FMI"){
        networkhandler_->fetchDataXML(datatype, location, startNendTime);
    }
    else if(source == "digitraffic"){
        networkhandler_->fetchDataJson(datatype, location, time, startNendTime);
    }
    else {
        networkhandler_->fetchDataXML(datatype, location, startNendTime);
        networkhandler_->fetchDataJson(datatype, location, time, startNendTime);
    }

}

void Controller::createDigiTrafficChart(std::unordered_map<QString, QString> data, QString datatype, std::vector<QString> coordinates, QString time)
{
    view_->createChart("traffic", datatype, data, {}, datatype, "observed");
}

void Controller::createFMIChart(std::unordered_map<QString, std::vector<double> > data, QString datatype)
{
    view_->createChart("weather", datatype, {}, data, "", "");
}

void Controller::createCombinedChart(std::unordered_map<QString, std::vector<double>> FMIdata,
                                    std::unordered_map<QString, std::vector<double>> digiTrafficData, QString datatype)
{
    view_->createChart("weather", datatype, {}, FMIdata, "", "");
}

std::tuple<QString, QString> Controller::parseTimeDate(QString t, QString type)
{
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);

    localTime->tm_hour -= 2;

    if (type == "observed" || type == "maintenance"){


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
