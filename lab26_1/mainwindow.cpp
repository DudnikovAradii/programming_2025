#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// Класс "Точка интереса"
class PointOfInterest {
private:
    QString name_;
    QString description_;
    int complexity_;
    QString coord_x_;   // ← теперь строки
    QString coord_y_;

public:
    PointOfInterest(QString name, QString description, int complexity, QString coord_x, QString coord_y)
        : name_(name), description_(description), complexity_(complexity), coord_x_(coord_x), coord_y_(coord_y) {}

    void saveToDataJson() {
        json pointsArray;
        const string filename = "data.json";

        ifstream inFile(filename);
        if (inFile.is_open()) {
            try {
                inFile >> pointsArray;
                if (!pointsArray.is_array()) {
                    pointsArray = json::array();
                }
            } catch (...) {
                pointsArray = json::array();
            }
            inFile.close();
        } else {
            pointsArray = json::array();
        }

        json newPoint = {
            {"name", name_.toStdString()},
            {"description", description_.toStdString()},
            {"complexity", complexity_},

            // 🔥 ключевое изменение
            {"coord_x", coord_x_.isEmpty() ? "" : coord_x_.toStdString()},
            {"coord_y", coord_y_.isEmpty() ? "" : coord_y_.toStdString()}
        };

        pointsArray.push_back(newPoint);

        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << pointsArray.dump(4);
            outFile.close();

            QMessageBox::information(nullptr, "Успех",
                                     QString("Точка интереса \"%1\" успешно добавлена!").arg(name_));
        } else {
            QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть data.json!");
        }
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Новая точка интереса");
    setMinimumSize(550, 500);
    setStyleSheet("QMainWindow { background-color: #f0f0f0; }");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(15);

    // Группа ввода
    QGroupBox *inputGroup = new QGroupBox("Параметры точки интереса");
    inputGroup->setStyleSheet("QGroupBox { font-weight: bold; font-size: 12px; }");

    QFormLayout *formLayout = new QFormLayout(inputGroup);
    formLayout->setSpacing(10);

    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Введите название");
    nameEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }");
    formLayout->addRow("Название:", nameEdit);

    descriptionEdit = new QTextEdit();
    descriptionEdit->setPlaceholderText("Введите описание");
    descriptionEdit->setMaximumHeight(80);
    descriptionEdit->setStyleSheet("QTextEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }");
    formLayout->addRow("Описание:", descriptionEdit);

    complexityEdit = new QLineEdit();
    complexityEdit->setPlaceholderText("1-10");
    complexityEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }");
    formLayout->addRow("Сложность (1-10):", complexityEdit);

    coordXEdit = new QLineEdit();
    coordXEdit->setPlaceholderText("0.0");
    coordXEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }");
    formLayout->addRow("Координата X:", coordXEdit);

    coordYEdit = new QLineEdit();
    coordYEdit->setPlaceholderText("0.0");
    coordYEdit->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid #ccc; border-radius: 3px; }");
    formLayout->addRow("Координата Y:", coordYEdit);

    mainLayout->addWidget(inputGroup);

    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);

    confirmButton = new QPushButton("OK");
    confirmButton->setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; font-size: 14px; font-weight: bold; "
        "padding: 10px; border-radius: 5px; min-width: 120px; }"
        "QPushButton:hover { background-color: #45a049; }"
        );

    loadTxtButton = new QPushButton("Из .txt");
    loadTxtButton->setStyleSheet(
        "QPushButton { background-color: #2196F3; color: white; font-size: 14px; font-weight: bold; "
        "padding: 10px; border-radius: 5px; min-width: 120px; }"
        "QPushButton:hover { background-color: #0b7dda; }"
        );

    buttonLayout->addWidget(confirmButton);
    buttonLayout->addWidget(loadTxtButton);
    mainLayout->addLayout(buttonLayout);

    // Подсказка
    QLabel *infoLabel = new QLabel(
        "Формат TXT файла (5 строк):\n"
        "1 - Название\n"
        "2 - Описание\n"
        "3 - Сложность\n"
        "4 - Координата X\n"
        "5 - Координата Y");
    infoLabel->setStyleSheet("color: #666; font-size: 10px; background-color: #f9f9f9; padding: 10px; border-radius: 5px;");
    infoLabel->setWordWrap(true);
    mainLayout->addWidget(infoLabel);

    connect(confirmButton, &QPushButton::clicked, this, &MainWindow::onConfirmClicked);
    connect(loadTxtButton, &QPushButton::clicked, this, &MainWindow::onLoadTxtClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onConfirmClicked()
{
    QString name = nameEdit->text();
    QString description = descriptionEdit->toPlainText();
    int complexity = complexityEdit->text().toInt();

    // 🔥 теперь строки
    QString coordXStr = coordXEdit->text();
    QString coordYStr = coordYEdit->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поле 'Название' обязательно!");
        return;
    }

    PointOfInterest newPoint(name, description, complexity, coordXStr, coordYStr);
    newPoint.saveToDataJson();

    nameEdit->clear();
    descriptionEdit->clear();
    complexityEdit->clear();
    coordXEdit->clear();
    coordYEdit->clear();
}

void MainWindow::onLoadTxtClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите TXT файл", "", "Text Files (*.txt)");

    if (fileName.isEmpty()) return;

    vector<string> lines;
    ifstream file(fileName.toStdString());
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    if (lines.size() >= 5) {
        nameEdit->setText(QString::fromStdString(lines[0]));
        descriptionEdit->setText(QString::fromStdString(lines[1]));
        complexityEdit->setText(QString::fromStdString(lines[2]));
        coordXEdit->setText(QString::fromStdString(lines[3]));
        coordYEdit->setText(QString::fromStdString(lines[4]));

        QMessageBox::information(this, "Загрузка", "Данные загружены!");
    } else {
        QMessageBox::warning(this, "Ошибка", "Файл должен содержать минимум 5 строк!");
    }
}
