#include "controller.h"
#include <ctime>
#include <string>


Controller::Controller(NetworkHandler* networkhandler, MainWindow* view)
    : networkhandler_(networkhandler),
    view_(view)
{
    // connect fetch data button from frontend to controller
    connect(view_, &MainWindow::fetchDigiTraffic, this, &Controller::pushButtonClicked);
    connect(view_, &MainWindow::fetchFMI, this, &Controller::pushButtonClicked);

    // Connect signal that data fetching is done and data is parsed
    connect(networkhandler_, &NetworkHandler::jsonReady, this, &Controller::createDigiTrafficChart);
    connect(networkhandler_, &NetworkHandler::xmlReady, this, &Controller::createFMIChart);
}

Controller::~Controller()
{
    delete networkhandler_;
    delete view_;
}
/**
 * @brief Controller::pushButtonClicked
 * Handles the functionality after user clicks fetch button after selecting preferences for data
 * @param source
 * Source of data, fmi or digitraffic
 * @param datatype
 * Type of data selected by user
 * @param location
 * Selected city
 * @param time
 * Selected timeline
 */
void Controller::pushButtonClicked(QString source, QString datatype,
                                   QString location, QString time )
{
    // Get the start and end time of
    std::tuple<QString, QString> startNendTime = parseTimeDate(time, datatype);

    source_ = source;
    datatype_ = datatype;
    location_ = location;

    // Set flags for data readyness for combined data
    digitrafficReady = false;
    fmiReady = false;

    // Operations based on source, FMI, digitraffic or both
    if(source == "FMI"){
        networkhandler_->fetchDataXML(datatype, location, startNendTime);
    }
    else if(source == "digitraffic"){
        networkhandler_->fetchDataJson(datatype, location, time, startNendTime);
    }
    else {
        networkhandler_->fetchDataXML("observed", location, startNendTime);
        networkhandler_->fetchDataJson("maintenance", location, time, startNendTime);
    }
}

/**
 * @brief Controller::createDigiTrafficChart
     Function for calling the function creating chart from digitraffic data.
     Takes traffic data and datatype as parameters. Also calls the
     function to create combined chart if source has been both API's
 * @param data
     Traffic data
 * @param datatype
     what data is fetched from the API
 */
void Controller::createDigiTrafficChart(std::unordered_map<QString, QString> data, QString datatype)
{
    if (source_ == "digitraffic"){
        view_->createChart("traffic", datatype, data, {});
    }
    else {
        digitrafficData = data;
        digitrafficReady = true;
        createCombinedChart();
    }
}

/**
 * @brief Controller::createFMIChart
     Function for calling the function creating chart from FMI data.
     Takes weather data and datatype as parameters. Also calls the
     function to create combined chart if source has been both API's
 * @param data
     Weather data
 * @param datatype
     what data is fetched from the API
 */
void Controller::createFMIChart(std::unordered_map<QString, std::vector<double> > data, QString datatype)
{
    if (source_ == "FMI"){
        view_->createChart("weather", datatype, {}, data);
    }
    else {
        fmiData = data;
        fmiReady = true;
        createCombinedChart();
    }
}

/**
 * @brief Controller::createCombinedChart
     Function for calling the function creating chart from the data of both API's.
 */
void Controller::createCombinedChart()
{
    if (fmiReady == true && digitrafficReady == true){
        view_->createChart("combined", "", digitrafficData, fmiData);
    }
}

/**
 * @brief Controller::parseTimeDate
 * Gets and formats a TimeDate pair of current time and endtime for api fetching
 * @param t
 * timeline selected by user over witch data is to be fetched
 * @param type
 * Datatype, whether times are wanted for observations or forecast
 * @return tuple<QString, QString>
 *  pair of times formatted to ISO 8601 format
 */
std::tuple<QString, QString> Controller::parseTimeDate(QString t, QString type)
{
    // Get current computer time using ctime class
    char format [50];
    time_t currentTime = time(0);
    tm *localTime = localtime(&currentTime);

    // Due to FMI api not providing observed data for the last 2 hours our "current time" is 2 hours before the function run time
    localTime->tm_hour -= 2;

    // if - else to check if wanted time is t hours before now or from now
    if (type == "observed" || type == "maintenance" || type == ""){
        if (t == "2"){

            strftime(format, sizeof(format), "%Y-%m-%dT%H:00:00Z", localTime);
            QString endtime = format;
            if (localTime->tm_hour < 2){
                int diff = localTime->tm_hour - 2;
                localTime->tm_hour = 24 + diff;
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
                localTime->tm_hour = 24 + diff;
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
                localTime->tm_hour = 24 + diff;
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
                localTime->tm_hour = 24 + diff;
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
