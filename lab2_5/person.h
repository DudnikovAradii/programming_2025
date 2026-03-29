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

    bool isValidName(const QString& s) const {
        if (s.isEmpty()) return false;
        // Проверяем русское имя (первая буква заглавная, остальные строчные)
        QRegularExpression reRus("^[А-ЯЁ][а-яё]{0,49}$");
        // Проверяем английское имя (первая буква заглавная, остальные строчные)
        QRegularExpression reEng("^[A-Z][a-z]{0,49}$");
        return reRus.match(s).hasMatch() || reEng.match(s).hasMatch();
    }

public:
    Person() : birthDate_() {}

    virtual ~Person() {}

    virtual QString getFullName() const {
        return QString("%1 %2").arg(lastName_).arg(firstName_);
    }

    virtual void craft(QWidget* parent_ = nullptr) = 0;

    Date getBirthDate() const { return birthDate_; }
    void setBirthDate(const Date& date_) { birthDate_ = date_; }

    QString getFirstName() const { return firstName_; }
    QString getLastName() const { return lastName_; }

    bool setFirstName(const QString& name_) {
        if (isValidName(name_)) {
            firstName_ = name_;
            return true;
        }
        qDebug() << "Ошибка: неверное имя" << name_ << "- только буквы (1-50 символов)";
        return false;
    }

    bool setLastName(const QString& name_) {
        if (isValidName(name_)) {
            lastName_ = name_;
            return true;
        }
        qDebug() << "Ошибка: неверная фамилия" << name_ << "- только буквы (1-50 символов)";
        return false;
    }
};

#endif // PERSON_H
