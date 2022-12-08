#include "utils.h"
#include <QXmlStreamReader>
#include <QDebug>

utils::utils()
{

}

/**
 * @brief utils::getCoordinates
     Function for converting the selected city into coordinates
 * @param location
     The city that the user has selected
 * @return std::vector<QString>
     A vector which has the coordinates
 */
std::vector<QString> utils::getCoordinates(QString location)
{
    if (location == "Tampere"){
        return std::vector<QString> {"23.7", "61.4", "23.8", "61.5"};
    }
    else if (location == "Helsinki"){
        return std::vector<QString> {"24.9", "60.1", "25.0", "60.2"};
    }
    else if (location == "Turku"){
        return std::vector<QString> {"22.2", "60.4", "22.3", "60.5"};
    }
    else if (location == "Oulu"){
        return std::vector<QString> {"25.4", "65.0", "25.5", "65.1"};
    }
    else if (location == "Jyväskylä"){
        return std::vector<QString> {"25.7", "62.2", "25.8", "62.3"};
    }

}

QString utils::getGeoID(QString location)
{
    if (location == "Tampere"){
        return QString("634963");
    }
    else if (location == "Helsinki"){
        return QString("658225");
    }
    else if (location == "Turku"){
        return QString("633679");
    }
    else if (location == "Oulu"){
        return QString("643492");
    }
    else if (location == "Jyväskylä"){
        return QString("655194");
    }
}

/**
 * @brief utils::parseJson
     Function for parsing the digitraffic data
 * @param datatype
     What data is fetched from the API
 * @param jsonData
     The digitraffic data as QJsonObject
 * @param time
     From which time the data is wanted
 * @param coordinates
     From which location the data is wanted
 * @return std::unordered_map<QString, QString>
     The data parsed and inserted into unordered map
 */
std::unordered_map<QString, QString> utils::parseJson(QJsonObject jsonData, QString datatype, std::vector<QString> coordinates, QString time)
{
    std::unordered_map<QString, QString> digitrafficData;

    if(datatype == "maintenance"){
        QJsonArray maintenanceFeatures = jsonData["features"].toArray();
        //variable for making unique key for the datastructure
        int counter = 1;
        //every maintenance task from the data inserted into the datastructure
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
        //intializing the desired time for the data
        int forecast = 1;
        if(time == "4"){
            forecast = 2;
        }
        else if(time == "6"){
            forecast = 3;
        }
        else if(time == "12"){
            forecast = 4;
        }

        //data parsed as QString's
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
        QString windSpeed = QString::number(roadConditions[forecast].toObject()
             .value("windSpeed").toInt());
        QString windDirection = QString::number(roadConditions[forecast].toObject()
             .value("windDirection").toInt());
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
            //data parsed as QString and QJsonArray
            QString type = ele.toObject().value("geometry")
                               .toObject().value("type").toString();
            QJsonArray coords = ele.toObject().value("geometry")
                                    .toObject().value("coordinates").toArray();

            //the amount of traffic messages in the desired location is counted
            //from the different coordinate types that the data had
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
    return digitrafficData;
}


std::unordered_map<QString, std::vector<double> > utils::parseXML(QString content)
{
    // Parses XML document from FMI api to values which are used with graphs
    QXmlStreamReader reader(content);

    QString type;
    std::vector<double> temperature;
    std::vector<double> windspeed;
    std::vector<double> avgtemp;
    std::vector<double> mintemp;
    std::vector<double> maxtemp;

    while (!reader.atEnd()) {
        if ( reader.name() == QString("Time")) {
            QString time = reader.readElementText();
        }
        else if (reader.name() ==QString( "ParameterName")){
            type = reader.readElementText();
        }
        else if (reader.name() == QString("ParameterValue")){
            QString XMLvalue = reader.readElementText();
            double value;
            if (XMLvalue == "NaN"){
                qDebug() << "No value";
                // Naive for now and insert value 0 when there isnt any data from api
                value = 0;
            }
            else{
                value = XMLvalue.toDouble();
            }
            if (type == "t2m" || type == "temperature"){
                temperature.push_back(value);
            }
            else if (type == "ws_10min" ||type == "windspeedms"){
                windspeed.push_back(value);
            }
            else if (type == "tday") {
                avgtemp.push_back(value);
            }
            else if(type == "tmax"){
                maxtemp.push_back(value);
            }
            else if(type == "tmin") {
                mintemp.push_back(value);
            }

        }
        reader.readNext();
    }
    std::unordered_map<QString, std::vector<double>> FMIdata = {
    {"temperature", temperature},
     {"windspeed", windspeed},
        {"avgtemp", avgtemp},
        {"mintemp", mintemp},
        {"maxtemp", maxtemp}
    };
    return FMIdata;
}
