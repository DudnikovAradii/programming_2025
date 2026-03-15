#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QRegularExpressionValidator>

#include "person.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QRadioButton;
class QPushButton;
class QLabel;
class QButtonGroup;
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSaveButtonClicked();
    void onResetButtonClicked();

private:
    //Поля
    QLineEdit* subjectEdit;
    QLineEdit* teacherEdit;
    QLineEdit* audienceEdit;
    QLineEdit* scheduleNumberEdit;

    // Тип занятия
    QRadioButton* lectureRadio;
    QRadioButton* practiceRadio;
    QButtonGroup* typeGroup; //Групппа(только одна кнопка должна быть выбрана)

    // Ожидания
    QCheckBox* testCheck;
    QCheckBox* attendanceCheck;
    QCheckBox* cancelCheck;

    //Кнопки
    QPushButton* saveButton;
    QPushButton* resetButton;

    // Метки ошибок
    QLabel* subjectError;
    QLabel* teacherError;
    QLabel* audienceError;
    QLabel* scheduleError;
    QLabel* typeError;

    // Проверщики ввода(проверяют каждый символ и не дают ввести неправильные символы)
    QRegularExpressionValidator* subjectValidator;
    QRegularExpressionValidator* teacherValidator;
    QRegularExpressionValidator* audienceValidator;
    QRegularExpressionValidator* scheduleValidator;

    // Вспомогательные методы
    void setupValidators(); //Создает и настраивает все валидаторы
    void setupUI();     //Создает все виджеты и размещает их на форме
    bool validateInputs(); //Проверяет все поля на ошибки(возвращает тру/фолс)
    void clearErrors(); //Прячет все сообщения об ошибках
    void saveToFile(const Person& person); //Сохраняет объект Person в файл
    QList<QString> getSelectedExpectations(); //Собирает выбранные чекбоксы в список
};

#endif // MAINWINDOW_H












