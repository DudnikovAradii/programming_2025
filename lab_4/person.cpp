#include "person.h"
#include <QDebug>  // Для отладочного вывода

//Конструкор с параметром
Person::Person(const QString& subject, const QString& teacher,
               const QString& audience, int scheduleNumber,
               const QString& lessonType,
               const QList<QString>& expectations): m_subject(subject),
                                                    m_teacher(teacher),
                                                    m_audience(audience),
                                                    m_scheduleNumber(scheduleNumber),
                                                    m_lessonType(lessonType),
                                                    m_expectations(expectations)
{
    qDebug() << "Cоздан объект Person для предмета: " << subject;
}

//Деструктор
Person::~Person()
{
    qDebug() << "Удален объект Person для предмета: " << m_subject;
}

// Запись в файл
void Person::writeToFile(QTextStream& out) const
{
    //Записываем данные в файл
    out << "   Информация о занятии   ";
    out << "Предмет: " << m_subject << "\n";
    out << "Преподаватель: " << m_teacher << "\n";
    out << "Аудитория: " << m_audience << "\n";
    out << "Номер пары: " << m_scheduleNumber << "\n";
    out << "Тип занятия: " << m_lessonType << "\n";

    //Проверка, есть ли ожидания
    if (!m_expectations.isEmpty()) {
        out << "Ожидания: ";
        for (int i = 0; i < m_expectations.size(); ++i) {
            out << m_expectations[i]; //Записываем ожидания
        if (i < m_expectations.size() - 1){
            out << ",";
            }
        }
        out << "\n";
    }
    out << "\n";
}













