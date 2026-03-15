#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Person
{
public:
    //Дефолт конструктор для объекта с данными
    Person(const QString& subject, const QString& teacher,
           const QString& audience, int scheduleNumber,
           const QString& lessonType,
           const QList<QString>& expectations); //QList аналог динамического массива который хранит в себе строки <QString>

    //Диструктор
    ~Person();

    //Метод для записи в файл
    void writeToFile(QTextStream& out) const; // QTextStream — класс Qt для работы с текстом (запись/чтение строк)

    //Геттеры
    QString getSubject() const { return m_subject; }
    QString getTeacher() const {return m_teacher; }
    QString getAudience() const { return m_audience; }
    int getScheduleNumber() const { return m_scheduleNumber; }
    QString getLessonType() const { return m_lessonType; }
    QList<QString> getExpectations() const { return m_expectations; }

    //Сеттеры
    void setSubject(const QString& subject) { m_subject = subject; }
    void setTeacher(const QString& teacher) { m_teacher = teacher; }
    void setAudience(const QString& audience) { m_audience = audience; }
    void setScheduleNumber(int number) { m_scheduleNumber = number; }
    void setLessonType(const QString& type) { m_lessonType = type; }
    void setExpectations(const QList<QString>& expectations) { m_expectations = expectations; }

private:
    QString m_subject;        // Предмет
    QString m_teacher;        // ФИО
    QString m_audience;       // Номер аудитории
    int m_scheduleNumber;     // Номер пары в расписании (1-8)
    QString m_lessonType;     // Тип занятия
    QList<QString> m_expectations;  // Список ожиданий
};

#endif
















