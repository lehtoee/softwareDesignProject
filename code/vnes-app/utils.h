#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <QString>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <qjsonobject.h>
#include <QJsonArray>


class utils
{
public:
    utils();
    std::vector<QString> getCoordinates(QString location);
    QString getGeoID(QString location);
    std::unordered_map<QString, std::vector<double>> parseXML(QString content);
    std::unordered_map<QString, QString> parseJson(QJsonObject jsonData, QString datatype,
                                                   std::vector<QString> coordinates, QString time);
};

#endif // UTILS_H
