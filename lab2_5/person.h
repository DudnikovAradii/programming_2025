#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QWidget>
#include <QRegularExpression>
#include <QDebug>
#include "date.h"

class Person {
protected:
    QString firstName_;
    QString lastName_;
    Date birthDate_;

    DateFormat format_ = DateFormat::Russian;

    bool isValidName(const QString& s) const {
        if (s.isEmpty()) return false;

        QRegularExpression reRus("^[А-ЯЁ][а-яё]{0,49}$");
        QRegularExpression reEng("^[A-Z][a-z]{0,49}$");

        return reRus.match(s).hasMatch() || reEng.match(s).hasMatch();
    }

public:
    Person() : birthDate_() {}
    virtual ~Person() {}

    void setFormat(DateFormat f) { format_ = f; }

    virtual QString getFullName() const {
        return QString("%1 %2").arg(lastName_).arg(firstName_);
    }

    virtual void craft(QWidget* parent_ = nullptr) = 0;

    virtual QString getFormattedBirthDate() const {
        return birthDate_.toString(format_);
    }

    void setBirthDate(const Date& date_) { birthDate_ = date_; }

    bool setFirstName(const QString& name_) {
        if (isValidName(name_)) {
            firstName_ = name_;
            return true;
        }
        return false;
    }

    bool setLastName(const QString& name_) {
        if (isValidName(name_)) {
            lastName_ = name_;
            return true;
        }
        return false;
    }
};

#endif
