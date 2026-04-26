#include "pointofinterest.h"
#include <cmath>
#include <QRegularExpression>

QJsonObject PointOfInterest::toJson() const
{
    QJsonObject obj;
    obj["name"] = name;
    obj["description"] = description;
    obj["difficulty"] = difficulty;
    obj["x"] = x;
    obj["y"] = y;
    return obj;
}

PointOfInterest PointOfInterest::fromJson(const QJsonObject &obj)
{
    PointOfInterest p;
    p.name = obj["name"].toString();
    p.description = obj["description"].toString();
    p.difficulty = obj["difficulty"].toInt();
    p.x = obj["x"].toDouble();
    p.y = obj["y"].toDouble();
    return p;
}

bool PointOfInterest::hasDigitsInNameOrDescription() const
{
    QRegularExpression regex("\\d");
    return name.contains(regex) || description.contains(regex);
}

bool PointOfInterest::isValid() const
{
    if (name.isEmpty() || description.isEmpty())
        return false;

    if (hasDigitsInNameOrDescription())
        return false;

    if (difficulty < 1 || difficulty > 10)
        return false;

    if (std::isnan(x) || std::isnan(y))
        return false;

    if (std::isinf(x) || std::isinf(y))
        return false;

    return true;
}
