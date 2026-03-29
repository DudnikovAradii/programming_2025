#ifndef RUSSIANPERSON_H
#define RUSSIANPERSON_H

#include "person.h"

class RussianPerson : public Person {
private:
    QString patronymic_;

    bool isValidPatronymic(const QString& s) const {
        if (s.isEmpty()) return true; // отчество может быть пустым
        QRegularExpression re("^[А-ЯЁ][а-яё]{0,49}$");
        return re.match(s).hasMatch();
    }

public:
    RussianPerson();
    RussianPerson(const QString& lastName_, const QString& firstName_,
                  const QString& patronymic_, const Date& birthDate_);

    QString getFullName() const override;
    void craft(QWidget* parent_ = nullptr) override;

    bool setPatronymic(const QString& patr_);
    QString getPatronymic() const { return patronymic_; }
};

#endif // RUSSIANPERSON_H
