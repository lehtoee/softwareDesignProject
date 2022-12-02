#include "utils.h"
#include <QXmlStreamReader>
#include <QDebug>

utils::utils()
{

}

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

std::unordered_map<QString, std::vector<double> > utils::parseXML(QString content)
{
    // Parses XML document from FMI api to values which are used with graphs
    QXmlStreamReader reader(content);

    QString type;
    std::vector<double> temperature;
    std::vector<double> windspeed;

    while (!reader.atEnd()) {
        if ( reader.name() == QString("Time")) {
            QString time = reader.readElementText();
            qDebug() << time;
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
            if (type == "t2m"){
                temperature.push_back(value);
            }
            else if (type == "ws_10min"){
                windspeed.push_back(value);
            }

        }
        reader.readNext();
    }
    std::unordered_map<QString, std::vector<double>> FMIdata = {
    {"Temperature", temperature},
     {"windspeed", windspeed}     };
    return FMIdata;
}


