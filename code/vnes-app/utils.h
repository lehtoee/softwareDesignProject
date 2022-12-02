#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <QString>
#include <unordered_map>
#include <tuple>
#include <vector>


class utils
{
public:
    utils();
    std::vector<QString> getCoordinates(QString location);
    QString getGeoID(QString location);
    std::unordered_map<QString, std::vector<double>> parseXML(QString content);
};

#endif // UTILS_H
