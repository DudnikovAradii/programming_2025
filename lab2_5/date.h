#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QDebug>
#include <QRegularExpression>

enum class DateFormat {
    Russian,   // дд.мм.гггг
    American   // мм-дд-гггг
};

struct Date {
private:
    int day_;
    int month_;
    int year_;

    bool isValidDate(int d, int m, int y) const {
        return isValidDateStatic(d, m, y);
    }

public:
    Date() : day_(1), month_(1), year_(2000) {}
    Date(int d, int m, int y) {
        if (isValidDate(d, m, y)) {
            day_ = d;
            month_ = m;
            year_ = y;
        } else {
            qDebug() << "Ошибка: неверная дата" << d << m << y;
            day_ = 1;
            month_ = 1;
            year_ = 2000;
        }
    }

    static bool isValidDateStatic(int d, int m, int y) {
        if (y < 1900 || y > 2026) return false;
        if (m < 1 || m > 12) return false;

        int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

        // Високосный год
        if (m == 2 && isLeapYearStatic(y)) {
            daysInMonth[1] = 29;
        }

        return d >= 1 && d <= daysInMonth[m - 1];
    }

    // Проверка високосного года
    static bool isLeapYearStatic(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static bool validateDateString(const QString& str, DateFormat format) {
        QRegularExpression re;

        if (format == DateFormat::Russian) {
            // дд.мм.гггг
            re.setPattern(R"(^(\d{2})\.(\d{2})\.(\d{4})$)");
        } else {
            // мм-дд-гггг
            re.setPattern(R"(^(\d{2})-(\d{2})-(\d{4})$)");
        }

        auto match = re.match(str);
        if (!match.hasMatch()) return false;

        int day, month, year;

        if (format == DateFormat::Russian) {
            day = match.captured(1).toInt();
            month = match.captured(2).toInt();
            year = match.captured(3).toInt();
        } else {
            month = match.captured(1).toInt();
            day = match.captured(2).toInt();
            year = match.captured(3).toInt();
        }

        return isValidDateStatic(day, month, year);
    }

    QString toString(DateFormat format) const {
        if (format == DateFormat::Russian) {
            // дд.мм.гггг
            return QString("%1.%2.%3")
                .arg(day_, 2, 10, QChar('0'))
                .arg(month_, 2, 10, QChar('0'))
                .arg(year_);
        } else {
            // мм-дд-гггг
            return QString("%1-%2-%3")
                .arg(month_, 2, 10, QChar('0'))
                .arg(day_, 2, 10, QChar('0'))
                .arg(year_);
        }
    }

    // Геттеры
    int getDay() const { return day_; }
    int getMonth() const { return month_; }
    int getYear() const { return year_; }

    // Проверка текущего объекта
    bool isValid() const {
        return isValidDate(day_, month_, year_);
    }
};

#endif // DATE_H
