#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include <QString>
#include <QJsonObject>
#include <cmath>

class PointOfInterest
{
public:
    QString name;
    QString description;
    int difficulty;
    double x;
    double y;

    QJsonObject toJson() const;
    static PointOfInterest fromJson(const QJsonObject &obj);

    bool isValid() const;
    bool hasDigitsInNameOrDescription() const;
};

#endif
