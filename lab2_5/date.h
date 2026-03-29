#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QDebug>

struct Date {
private:
    int day_;
    int month_;
    int year_;

    bool isValidDate(int d, int m, int y) const {
        if (y < 1900 || y > 2026) return false;
        if (m < 1 || m > 12) return false;

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Проверка на високосный год
        if (m == 2 && isLeapYear(y)) {
            daysInMonth[1] = 29;
        }

        if (d < 1 || d > daysInMonth[m - 1]) return false;

        return true;
    }

    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

public:
    Date() : day_(1), month_(1), year_(2000) {}

    Date(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day_ = d;
            month_ = m;
            year_ = y;
        } else {
            qDebug() << "Ошибка: неверная дата" << d << "." << m << "." << y;
            qDebug() << "Установлена дата по умолчанию: 01.01.2000";
            day_ = 1;
            month_ = 1;
            year_ = 2000;
        }
    }

    int getDay() const { return day_; }
    int getMonth() const { return month_; }
    int getYear() const { return year_; }

    void setDay(int d) {
        if (isValidDate(d, month_, year_)) {
            day_ = d;
        } else {
            qDebug() << "Ошибка: неверный день" << d;
        }
    }

    void setMonth(int m) {
        if (isValidDate(day_, m, year_)) {
            month_ = m;
        } else {
            qDebug() << "Ошибка: неверный месяц" << m;
        }
    }

    void setYear(int y) {
        if (isValidDate(day_, month_, y)) {
            year_ = y;
        } else {
            qDebug() << "Ошибка: неверный год" << y;
        }
    }

    QString toString() const {
        return QString("%1.%2.%3")
        .arg(day_, 2, 10, QChar('0'))
            .arg(month_, 2, 10, QChar('0'))
            .arg(year_);
    }

    bool isValid() const {
        return isValidDate(day_, month_, year_);
    }
};

#endif // DATE_H
