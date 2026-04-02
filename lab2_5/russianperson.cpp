#include "russianperson.h"
#include "passform.h"

RussianPerson::RussianPerson() : Person() {
    setFormat(DateFormat::Russian);
}

RussianPerson::RussianPerson(const QString& lastName_, const QString& firstName_,
                             const QString& patronymic_, const Date& birthDate_) {
    this->lastName_ = lastName_;
    this->firstName_ = firstName_;
    this->patronymic_ = patronymic_;
    this->birthDate_ = birthDate_;

    setFormat(DateFormat::Russian);
}

QString RussianPerson::getFullName() const {
    if (patronymic_.isEmpty() || patronymic_ == "-")
        return QString("%1 %2").arg(lastName_).arg(firstName_);
    return QString("%1 %2 %3").arg(lastName_).arg(firstName_).arg(patronymic_);
}

void RussianPerson::craft(QWidget* parent_) {
    PassForm* form_ = new PassForm(this, parent_);
    form_->setAttribute(Qt::WA_DeleteOnClose);
    form_->show();
}

bool RussianPerson::setPatronymic(const QString& patr_) {
    if (isValidPatronymic(patr_)) {
        patronymic_ = patr_;
        return true;
    }
    return false;
}
