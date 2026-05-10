#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QRegularExpression>
#include <QBrush>

#include <algorithm>
#include <fstream>
#include <vector>
#include <string>

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct ValidatedPoint
{
    string name;
    string description;
    int complexity;
    QString coord_x;
    QString coord_y;
    bool isValid;
    vector<bool> fieldErrors;
};

// УБИРАЕМ ЛИШНИЕ НУЛИ
QString normalizeNumber(const QString& str)
{
    bool ok;
    double num = str.toDouble(&ok);
    if (!ok)
        return str;
    return QString::number(num, 'g', 15);
}

// ПРОВЕРКИ
bool isNumeric(const string& s)
{
    if (s.empty())
        return false;
    try
    {
        size_t pos;
        stod(s, &pos);
        return pos == s.size();
    }
    catch (...)
    {
        return false;
    }
}

bool isValidName(const string& s)
{
    if (s.empty())
        return false;
    QRegularExpression regex("^[A-Za-zА-Яа-я0-9\\s\\-]+$");
    return regex.match(QString::fromStdString(s)).hasMatch();
}

bool isValidDescription(const string& s)
{
    if (s.empty())
        return false;
    QRegularExpression regex("^[A-Za-zА-Яа-я0-9\\s\\.,!?;:()\\-]+$");
    return regex.match(QString::fromStdString(s)).hasMatch();
}
bool isValidComplexity(int val)
{
    return val >= 1 && val <= 10;
}

// ОБРАТНЫЙ АЛФАВИТ
bool compareByName(const ValidatedPoint& a, const ValidatedPoint& b)
{
    return a.name > b.name;
}

// КОНСТРУКТОР
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Просмотр и валидация точек интереса");

    setMinimumSize(1300, 700);

    QWidget *centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *headerLayout = new QHBoxLayout();

    correctLabel = new QLabel("КОРРЕКТНЫЕ ОБЪЕКТЫ");
    correctLabel->setAlignment(Qt::AlignCenter);

    incorrectLabel = new QLabel("НЕКОРРЕКТНЫЕ ОБЪЕКТЫ");
    incorrectLabel->setAlignment(Qt::AlignCenter);

    headerLayout->addWidget(correctLabel);
    headerLayout->addWidget(incorrectLabel);

    mainLayout->addLayout(headerLayout);

    QHBoxLayout *tablesLayout = new QHBoxLayout();

    correctTable = new QTableWidget();

    correctTable->setColumnCount(5);

    QStringList headers =
        {
            "Название",
            "Описание",
            "Сложность",
            "X",
            "Y"
        };

    correctTable->setHorizontalHeaderLabels(headers);

    correctTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    incorrectTable = new QTableWidget();

    incorrectTable->setColumnCount(5);

    incorrectTable->setHorizontalHeaderLabels(headers);

    incorrectTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tablesLayout->addWidget(correctTable);

    tablesLayout->addWidget(incorrectTable);

    mainLayout->addLayout(tablesLayout);

    loadButton = new QPushButton("Загрузить data.json");

    mainLayout->addWidget(loadButton);

    statusLabel = new QLabel("Готов");

    mainLayout->addWidget(statusLabel);

    connect(loadButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onLoadClicked);
}
MainWindow::~MainWindow()
{
}

// ЗАГРУЗКА JSON
void MainWindow::onLoadClicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            "Выберите data.json",
            "",
            "JSON Files (*.json)");
    if (fileName.isEmpty())
        return;
    ifstream file(fileName.toStdString());
    if (!file.is_open())
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Не удалось открыть data.json");

        return;
    }
    json data;
    file >> data;
    vector<ValidatedPoint> correctPoints;
    vector<ValidatedPoint> incorrectPoints;

    // ПРОВЕРКА ОБЪЕКТОВ
    for (const auto& item : data)
    {
        ValidatedPoint point;
        point.fieldErrors = vector<bool>(5, false);
        point.isValid = true;

        // NAME
        point.name = item.value("name", "");
        if (!isValidName(point.name))
        {
            point.isValid = false;
            point.fieldErrors[0] = true;
        }

        // DESCRIPTION
        point.description = item.value("description", "");
        if (!isValidDescription(point.description))
        {
            point.isValid = false;
            point.fieldErrors[1] = true;
        }

        // COMPLEXITY
        if (item.contains("complexity") &&
            item["complexity"].is_number())
        {
            point.complexity = item["complexity"];
            if (!isValidComplexity(point.complexity))
            {
                point.isValid = false;
                point.fieldErrors[2] = true;
            }
        }
        else
        {
            point.isValid = false;
            point.fieldErrors[2] = true;
            point.complexity = 0;
        }

        // COORD X
        if (item.contains("coord_x"))
        {
            if (item["coord_x"].is_string())
            {
                string val = item["coord_x"];
                if (val.empty())
                {
                    point.isValid = false;
                    point.fieldErrors[3] = true;
                    point.coord_x = "";
                }
                else if (isNumeric(val))
                {
                    point.coord_x =
                        normalizeNumber(
                            QString::fromStdString(val));
                }
                else
                {
                    point.isValid = false;
                    point.fieldErrors[3] = true;
                    point.coord_x =
                        QString::fromStdString(val);
                }
            }
            else if (item["coord_x"].is_number())
            {
                point.coord_x =
                    normalizeNumber(
                        QString::number(
                            item["coord_x"].get<double>()));
            }
            else
            {
                point.isValid = false;
                point.fieldErrors[3] = true;
                point.coord_x = "";
            }
        }

        // COORD Y
        if (item.contains("coord_y"))
        {
            if (item["coord_y"].is_string())
            {
                string val = item["coord_y"];

                if (val.empty())
                {
                    point.isValid = false;
                    point.fieldErrors[4] = true;
                    point.coord_y = "";
                }
                else if (isNumeric(val))
                {
                    point.coord_y =
                        normalizeNumber(
                            QString::fromStdString(val));
                }
                else
                {
                    point.isValid = false;
                    point.fieldErrors[4] = true;
                    point.coord_y =
                        QString::fromStdString(val);
                }
            }
            else if (item["coord_y"].is_number())
            {
                point.coord_y =
                    normalizeNumber(
                        QString::number(
                            item["coord_y"].get<double>()));
            }
            else
            {
                point.isValid = false;
                point.fieldErrors[4] = true;
                point.coord_y = "";
            }
        }

        // РАЗДЕЛЕНИЕ
        if (point.isValid)
            correctPoints.push_back(point);
        else
            incorrectPoints.push_back(point);
    }

    // ОБРАТНАЯ СОРТИРОВКА
    sort(correctPoints.begin(),
         correctPoints.end(),
         compareByName);

    // СОХРАНЕНИЕ correct.json
    json correctJson = json::array();
    for (const auto& p : correctPoints)
    {
        correctJson.push_back({
            {"name", p.name},
            {"description", p.description},
            {"complexity", p.complexity},
            {"coord_x", p.coord_x.toStdString()},
            {"coord_y", p.coord_y.toStdString()}
        });
    }
    ofstream correctFile("correct.json");
    correctFile << correctJson.dump(4);
    correctFile.close();

    // СОХРАНЕНИЕ incorrect.json
    json incorrectJson = json::array();
    for (const auto& p : incorrectPoints)
    {
        incorrectJson.push_back({
            {"name", p.name},
            {"description", p.description},
            {"complexity", p.complexity},
            {"coord_x", p.coord_x.toStdString()},
            {"coord_y", p.coord_y.toStdString()}
        });
    }
    ofstream incorrectFile("incorrect.json");
    incorrectFile << incorrectJson.dump(4);
    incorrectFile.close();

    // ТАБЛИЦА CORRECT
    correctTable->setRowCount(correctPoints.size());
    for (size_t i = 0; i < correctPoints.size(); i++)
    {
        auto& p = correctPoints[i];

        correctTable->setItem(
            i,
            0,
            new QTableWidgetItem(
                QString::fromStdString(p.name)));

        correctTable->setItem(
            i,
            1,
            new QTableWidgetItem(
                QString::fromStdString(p.description)));

        correctTable->setItem(
            i,
            2,
            new QTableWidgetItem(
                QString::number(p.complexity)));

        correctTable->setItem(
            i,
            3,
            new QTableWidgetItem(p.coord_x));

        correctTable->setItem(
            i,
            4,
            new QTableWidgetItem(p.coord_y));
    }
    // ТАБЛИЦА INCORRECT
    incorrectTable->setRowCount(incorrectPoints.size());
    for (size_t i = 0; i < incorrectPoints.size(); i++)
    {
        const auto& p = incorrectPoints[i];
        QTableWidgetItem* nameItem =
            new QTableWidgetItem(
                QString::fromStdString(p.name));
        if (p.fieldErrors[0])
            nameItem->setBackground(QBrush(Qt::red));
        QTableWidgetItem* descItem =
            new QTableWidgetItem(
                QString::fromStdString(p.description));
        if (p.fieldErrors[1])
            descItem->setBackground(QBrush(Qt::red));
        QTableWidgetItem* compItem =
            new QTableWidgetItem(
                QString::number(p.complexity));
        if (p.fieldErrors[2])
            compItem->setBackground(QBrush(Qt::red));
        QTableWidgetItem* xItem =
            new QTableWidgetItem(p.coord_x);
        if (p.fieldErrors[3])
            xItem->setBackground(QBrush(Qt::red));
        QTableWidgetItem* yItem =
            new QTableWidgetItem(p.coord_y);
        if (p.fieldErrors[4])
            yItem->setBackground(QBrush(Qt::red));
        incorrectTable->setItem(i, 0, nameItem);
        incorrectTable->setItem(i, 1, descItem);
        incorrectTable->setItem(i, 2, compItem);
        incorrectTable->setItem(i, 3, xItem);
        incorrectTable->setItem(i, 4, yItem);
    }
    // СТАТУС
    statusLabel->setText(
        QString("Корректных: %1 | Некорректных: %2")
            .arg(correctPoints.size())
            .arg(incorrectPoints.size()));
}
