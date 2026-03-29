#include "americanperson.h"
#include "passform.h"

AmericanPerson::AmericanPerson() : Person() {}

AmericanPerson::AmericanPerson(const QString& firstName_, const QString& middleName_,
                               const QString& lastName_, const Date& birthDate_) {
    this->firstName_ = firstName_;
    this->lastName_ = lastName_;
    this->birthDate_ = birthDate_;

    // теперь middle name обязателен, проверяем сразу
    if (!setMiddleName(middleName_)) {
        qDebug() << "Ошибка: Middle name не может быть пустым или содержать недопустимые символы";
        this->middleName_ = "Unknown"; // или можно выбросить исключение
    }
}

QString AmericanPerson::getFullName() const {
    // теперь middle name всегда обязателен
    return QString("%1 %2 %3").arg(firstName_).arg(middleName_).arg(lastName_);
}

void AmericanPerson::craft(QWidget* parent_) {
    PassForm* form_ = new PassForm(this, parent_);
    form_->setAttribute(Qt::WA_DeleteOnClose);
    form_->show();
}

bool AmericanPerson::setMiddleName(const QString& mid_) {
    if (isValidMiddleName(mid_)) {
        middleName_ = mid_;
        return true;
    }
    qDebug() << "Ошибка: неверное middle name" << mid_;
    return false;
}
