#include "americanperson.h"
#include "passform.h"

AmericanPerson::AmericanPerson() : Person() {
    setFormat(DateFormat::American);
}

AmericanPerson::AmericanPerson(const QString& firstName_, const QString& middleName_,
                               const QString& lastName_, const Date& birthDate_) {
    this->firstName_ = firstName_;
    this->lastName_ = lastName_;
    this->birthDate_ = birthDate_;

    setFormat(DateFormat::American);

    if (!setMiddleName(middleName_)) {
        this->middleName_ = "Unknown";
    }
}

QString AmericanPerson::getFullName() const {
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
    return false;
}
