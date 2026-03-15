#include "mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRegularExpression>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Пара"); //Заголовок
    setMinimumSize(600, 400); //Размер окна
    setupValidators();
    setupUI();
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);
}

MainWindow::~MainWindow()
{
    delete subjectValidator;
    delete teacherValidator;
    delete audienceValidator;
    delete scheduleValidator;
}

void MainWindow::setupValidators()
{
    // Предмет: русские буквы, первая заглавная
    QRegularExpression subjectRegex("^[А-Я][а-я]*$");
    subjectValidator = new QRegularExpressionValidator(subjectRegex, this);

    // Преподаватель: Фамилия И.О.
    QRegularExpression teacherRegex("^[А-Я][а-я]*\\s[А-Я]\\.([А-Я]\\.)?$");
    teacherValidator = new QRegularExpressionValidator(teacherRegex, this);

    // Аудитория: 101-140,201-240,301-340,401-440 + буква А
    QRegularExpression audienceRegex("^(10[1-9]|1[1-3][0-9]|140|"
                                     "20[1-9]|2[1-3][0-9]|240|"
                                     "30[1-9]|3[1-3][0-9]|340|"
                                     "40[1-9]|4[1-3][0-9]|440)А?$");
    audienceValidator = new QRegularExpressionValidator(audienceRegex, this);

    // Номер пары: 1-8
    QRegularExpression scheduleRegex("^[1-8]$");
    scheduleValidator = new QRegularExpressionValidator(scheduleRegex, this);
}

void MainWindow::setupUI() // Cоздаем интерфейс
{
    QWidget* centralWidget = new QWidget(this); //Создает центральный виджет окна
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget); //Элементы будут располагаться сверху вниз

    // Группа ввода
    QGroupBox* inputGroup = new QGroupBox("Данные о занятии"); //рамка с заголовком "Данные о занятии"
    QGridLayout* grid = new QGridLayout(inputGroup); //таблица для размещения элементов внутри группы

    // Создание полей
    subjectEdit = new QLineEdit(); // создаем поле ввода
    subjectEdit->setPlaceholderText("Например: Математика"); //подсказка
    subjectEdit->setValidator(subjectValidator); //Прикрепляем обработчик ошибок

    teacherEdit = new QLineEdit();
    teacherEdit->setPlaceholderText("Например: Иванов И.И.");
    teacherEdit->setValidator(teacherValidator);

    audienceEdit = new QLineEdit();
    audienceEdit->setPlaceholderText("Например: 101 или 101А");
    audienceEdit->setValidator(audienceValidator);

    scheduleNumberEdit = new QLineEdit();
    scheduleNumberEdit->setPlaceholderText("1-8");
    scheduleNumberEdit->setValidator(scheduleValidator);
    scheduleNumberEdit->setMaxLength(1);

    // Тип занятия
    lectureRadio = new QRadioButton("Лекция");
    practiceRadio = new QRadioButton("Практика");
    typeGroup = new QButtonGroup(this);
    typeGroup->addButton(lectureRadio);
    typeGroup->addButton(practiceRadio);

    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(lectureRadio);
    typeLayout->addWidget(practiceRadio);
    typeLayout->addStretch();

    // Ожидания
    testCheck = new QCheckBox("Контрольная");
    attendanceCheck = new QCheckBox("Проверка посещений");
    cancelCheck = new QCheckBox("Отмена");

    QHBoxLayout* expectationsLayout = new QHBoxLayout();
    expectationsLayout->addWidget(testCheck);
    expectationsLayout->addWidget(attendanceCheck);
    expectationsLayout->addWidget(cancelCheck);
    expectationsLayout->addStretch();

    // Метки ошибок
    subjectError = new QLabel();
    subjectError->setVisible(false);

    teacherError = new QLabel();
    teacherError->setVisible(false);

    audienceError = new QLabel();
    audienceError->setVisible(false);

    scheduleError = new QLabel();
    scheduleError->setVisible(false);

    typeError = new QLabel();
    typeError->setVisible(false);

    // Добавление в сетку
    int row = 0;
    grid->addWidget(new QLabel("Предмет:"), row, 0);
    grid->addWidget(subjectEdit, row, 1, 1, 2);
    grid->addWidget(subjectError, row, 3);
    row++;

    grid->addWidget(new QLabel("Преподаватель:"), row, 0);
    grid->addWidget(teacherEdit, row, 1, 1, 2);
    grid->addWidget(teacherError, row, 3);
    row++;

    grid->addWidget(new QLabel("Аудитория:"), row, 0);
    grid->addWidget(audienceEdit, row, 1, 1, 2);
    grid->addWidget(audienceError, row, 3);
    row++;

    grid->addWidget(new QLabel("Номер пары:"), row, 0);
    grid->addWidget(scheduleNumberEdit, row, 1, 1, 2);
    grid->addWidget(scheduleError, row, 3);
    row++;

    grid->addWidget(new QLabel("Тип занятия:"), row, 0);
    grid->addLayout(typeLayout, row, 1, 1, 2);
    grid->addWidget(typeError, row, 3);
    row++;

    grid->addWidget(new QLabel("Ожидания:"), row, 0, Qt::AlignTop);
    grid->addLayout(expectationsLayout, row, 1, 1, 3);
    row++;

    mainLayout->addWidget(inputGroup);

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    saveButton = new QPushButton("Сохранить");
    resetButton = new QPushButton("Сброс");

    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(resetButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
}

void MainWindow::clearErrors()
{
    subjectError->setVisible(false);
    teacherError->setVisible(false);
    audienceError->setVisible(false);
    scheduleError->setVisible(false);
    typeError->setVisible(false);
}

QList<QString> MainWindow::getSelectedExpectations()
{
    QList<QString> selected;
    if (testCheck->isChecked())
        selected.append("Контрольная");
    if (attendanceCheck->isChecked())
        selected.append("Проверка посещений");
    if (cancelCheck->isChecked())
        selected.append("Отмена");
    return selected;
}

bool MainWindow::validateInputs() {
    clearErrors();
    bool isValid = true;
    int pos = 0;

    // Предмет
    if (subjectEdit->text().isEmpty()) {
        subjectError->setText("Обязательное поле");
        subjectError->setVisible(true);
        isValid = false;
    } else {
        QString text = subjectEdit->text();
        if (subjectValidator->validate(text, pos) != QValidator::Acceptable) {
            subjectError->setText("Предмет должен начинаться с заглавной буквы");
            subjectError->setVisible(true);
            isValid = false;
        }
    }

    // Преподаватель
    if (teacherEdit->text().isEmpty()) {
        teacherError->setText("Обязательное поле");
        teacherError->setVisible(true);
        isValid = false;
    } else {
        QString text = teacherEdit->text();
        pos = 0;
        if (teacherValidator->validate(text, pos) != QValidator::Acceptable) {
            teacherError->setText("Формат: Фамилия И.О. (например: Иванов И.И.)");
            teacherError->setVisible(true);
            isValid = false;
        }
    }

    // Аудитория
    if (audienceEdit->text().isEmpty()) {
        audienceError->setText("Обязательное поле");
        audienceError->setVisible(true);
        isValid = false;
    } else {
        QString text = audienceEdit->text();
        pos = 0;
        if (audienceValidator->validate(text, pos) != QValidator::Acceptable) {
            audienceError->setText("Аудитория должна быть 101-440, может быть с буквой А");
            audienceError->setVisible(true);
            isValid = false;
        }
    }

    // Номер пары
    if (scheduleNumberEdit->text().isEmpty()) {
        scheduleError->setText("Обязательное поле");
        scheduleError->setVisible(true);
        isValid = false;
    } else {
        QString text = scheduleNumberEdit->text();
        pos = 0;
        if (scheduleValidator->validate(text, pos) != QValidator::Acceptable) {
            scheduleError->setText("Номер пары должен быть от 1 до 8");
            scheduleError->setVisible(true);
            isValid = false;
        }
    }

    // Тип занятия (радиокнопки)
    if (!lectureRadio->isChecked() && !practiceRadio->isChecked()) {
        typeError->setText("Выберите тип занятия");
        typeError->setVisible(true);
        isValid = false;
    }

    return isValid;
}

void MainWindow::saveToFile(const Person& person)
{
    QFile file("result.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    person.writeToFile(out);

    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены в result.txt");
}

void MainWindow::onSaveButtonClicked()
{
    if (!validateInputs()) {
        QMessageBox::warning(this, "Ошибка", "Исправьте ошибки в форме");
        return;
    }

    QString lessonType = lectureRadio->isChecked() ? "Лекция" : "Практика";
    QList<QString> expectations = getSelectedExpectations();

    Person person(
        subjectEdit->text(),
        teacherEdit->text(),
        audienceEdit->text(),
        scheduleNumberEdit->text().toInt(),
        lessonType,
        expectations
        );

    saveToFile(person);

    qDebug() << "Сохранено:" << person.getSubject();
}

void MainWindow::onResetButtonClicked()
{
    subjectEdit->clear();
    teacherEdit->clear();
    audienceEdit->clear();
    scheduleNumberEdit->clear();

    lectureRadio->setChecked(false);
    practiceRadio->setChecked(false);

    testCheck->setChecked(false);
    attendanceCheck->setChecked(false);
    cancelCheck->setChecked(false);

    clearErrors();
}








