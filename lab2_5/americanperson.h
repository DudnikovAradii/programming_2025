#ifndef AMERICANPERSON_H
#define AMERICANPERSON_H

#include "person.h"
#include <QRegularExpression>

//Класс для американцев
class AmericanPerson : public Person {
private:
    QString middleName_;

    bool isValidMiddleName(const QString& s) const {
        if (s.isEmpty()) return false;
        QRegularExpression re("^[A-Z][a-z]{0,49}$");
        return re.match(s).hasMatch();
    }

public:

    AmericanPerson();
    AmericanPerson(const QString& firstName_, const QString& middleName_,
                   const QString& lastName_, const Date& birthDate_);

    QString getFullName() const override;
    void craft(QWidget* parent_ = nullptr) override;

    bool setMiddleName(const QString& mid_);
    QString getMiddleName() const { return middleName_; }
};

#endif // AMERICANPERSON_H
