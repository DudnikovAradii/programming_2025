#ifndef AMERICANPERSON_H
#define AMERICANPERSON_H

#include "person.h"

// КЛАСС ДЛЯ АМЕРИКАНЦЕВ (AmP)
// Добавляет поле "Middle name" (второе имя), теперь обязательное
class AmericanPerson : public Person {
private:
    QString middleName_;  // Middle name (второе имя)

    // ПРОВЕРКА MIDDLE NAME: только английские буквы, обязательно не пустое
    bool isValidMiddleName(const QString& s) const {
        if (s.isEmpty()) return false; // теперь пустое не допускается
        QRegularExpression re("^[A-Z][a-z]{0,49}$");
        return re.match(s).hasMatch();
    }

public:
    // КОНСТРУКТОРЫ
    AmericanPerson();
    AmericanPerson(const QString& firstName_, const QString& middleName_,
                   const QString& lastName_, const Date& birthDate_);

    // ПЕРЕОПРЕДЕЛЕНИЕ ВИРТУАЛЬНЫХ МЕТОДОВ
    QString getFullName() const override;  // Формат: "Джеймс Джозеф Парсонс"
    void craft(QWidget* parent_ = nullptr) override;  // Показать пропуск

    // Сеттер для middle name с проверкой
    bool setMiddleName(const QString& mid_);
    QString getMiddleName() const { return middleName_; }
};

#endif // AMERICANPERSON_H
